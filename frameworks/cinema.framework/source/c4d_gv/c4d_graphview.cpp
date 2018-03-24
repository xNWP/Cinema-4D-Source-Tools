#include "c4d_graphview.h"
#include "c4d_operatordata.h"
#include "c4d_particles.h"

////////////////////////////////

const String GvGetOperatorDetailedText(GvOperatorData *op, GvNode *bn)
{
	String text = op->GetText(bn);
	if (text.Content()) text = String(" (") + text + String(")");
	return bn->GetTitle() + text;
}

const String GvGetOperatorTitle(GvNode *bn, Int32 string_id)
{
	String title = bn->GetName(); return title.Content() ? title : GeLoadString(string_id);
}

////////////////////////////////

Bool GvGetPortDescription(GvPortsDescInfo *info, GvPortIO port, Int32 id, GvPortDescription *pd)
{
	Int32 i;

	if (info)
	{
		if (port == GV_PORT_INPUT || port == GV_PORT_INPUT_OR_GEDATA)
		{
			for (i = 0; i < info->in.count; ++i)
			{
				if (info->in.ids[i] == id)
				{
					if (info->in.name_ids) pd->name = GeLoadString(info->in.name_ids[i]);
					else if (info->in.names) pd->name = *info->in.names[i];
					else pd->name = String();
					pd->data_id = info->in.types[i];
					pd->flags = (GvPortDescFlags)info->in.flags[i];
					pd->parent_id = GV_PORT_INVALID_ID;
					return true;
				}
			}
		}
		else if (port == GV_PORT_OUTPUT)
		{
			for (i = 0; i < info->out.count; ++i)
			{
				if (info->out.ids[i] == id)
				{
					if (info->out.name_ids) pd->name = GeLoadString(info->out.name_ids[i]);
					else if (info->out.names) pd->name = *info->out.names[i];
					else pd->name = String();
					pd->data_id = info->out.types[i];
					pd->flags = (GvPortDescFlags)info->out.flags[i];
					pd->parent_id = GV_PORT_INVALID_ID;
					return true;
				}
			}
		}
	}
	return false;
}

////////////////////////////////

void GvFreeValuesTable(GvNode *bn, GvValue **&ports, Int32 &nr_of_ports)
{
	if (ports)
	{
		Int32 i;
		for (i = 0; i < nr_of_ports; ++i)
		{
			if (ports[i])
			{
				bn->FreeCalculationHandler(ports[i]);
				ports[i] = nullptr;
			}
		}
		bDelete(ports);
	}
	nr_of_ports = 0;
}

void GvFreeValuesTable(GvNode *bn, GvValuesInfo &info)
{
	if (!bn) return;

	if (info.in_values)
	{
		Int32 i;
		for (i = 0; i < info.nr_of_in_values; ++i)
		{
			if (info.in_values[i])
			{
				bn->FreeCalculationHandler(info.in_values[i]);
				info.in_values[i] = nullptr;
			}
		}
	}
	bDelete(info.in_values);
	info.nr_of_in_values = 0;
	bDelete(info.out_ports);
	info.nr_of_out_ports = 0;
}

Bool GvBuildInValuesTable(GvNode *bn, GvValue **&ports, Int32 &nr_of_ports, GvCalc *c, GvRun *r, GvIdTablePtr ids)
{
	Int32 i, entries = 0; GvPortDescription pd; GvPortListEntry *entry; Bool valid;

	nr_of_ports = 0;

	if (ids == GV_EXISTING_PORTS)
	{
		entries = bn->GetInPortCount();
		if (!entries) { ports = nullptr; return true; }

		ports = bNewDeprecatedUseArraysInstead<GvValue*>(entries);														// ports are initialized with nullptr
		if (!ports) goto error;

		for (i = 0; i < entries; ++i)
		{
			GvPort *port = bn->GetInPort(i); if (!port) goto error;
			ports[i] = bn->AllocCalculationHandler(port->GetMainID(), c, r, i);
			if (!ports[i]) goto error;
		}
	}
	else if (ids == GV_DEFINED_PORTS)
	{
		AutoAlloc<GvPortList> portlist; if (!portlist) return false;
		bn->GetPortList(GV_PORT_INPUT, portlist);
		entries = portlist->GetCount();
		if (!entries) { ports = nullptr; return true; }

		ports = bNewDeprecatedUseArraysInstead<GvValue*>(entries);													// ports are initialized with nullptr
		if (!ports) goto error;

		for (i = 0; i < entries; ++i)
		{
			entry = portlist->GetIndex(i);
			if (!entry || !bn->GetPortDescription(GV_PORT_INPUT, entry->id, &pd)) goto error;
			GvPort* port = bn->GetInPortFirstMainID(entry->id);
			if (!port && pd.ports_min > 0) goto error;

			valid = pd.flags & GV_PORTDESCRIPTION_MULTIPLE ?  port != nullptr : true;
			if (valid)
			{
				ports[i] = bn->AllocCalculationHandler(entry->id, c, r, GV_MULTIPLE_PORTS);
				if (!ports[i]) goto error;
			}
		}
	}
	else
	{
		for (entries = 0; ids[entries];) ++entries;
		if (!entries) { ports = nullptr; return true; }

		ports = bNewDeprecatedUseArraysInstead<GvValue*>(entries);													// ports are initialized with nullptr
		if (!ports) goto error;

		for (i = 0; i < entries; ++i)
		{
			if (!bn->GetPortDescription(GV_PORT_INPUT, ids[i], &pd)) goto error;
			GvPort* port = bn->GetInPortFirstMainID(ids[i]);
			if (!port && pd.ports_min > 0) goto error;

			valid = pd.flags & GV_PORTDESCRIPTION_MULTIPLE ?  port != nullptr : true;
			if (valid)
			{
				ports[i] = bn->AllocCalculationHandler(ids[i], c, r, GV_MULTIPLE_PORTS);
				if (!ports[i]) goto error;
			}
		}
	}
	nr_of_ports = entries;
	return true;

error:
	GvFreeValuesTable(bn, ports, entries);
	return false;
}

Bool GvCalculateInValuesTable(GvNode *bn, GvRun *run, GvCalc *calc, GvValuesInfo &info, Int32 singleport, BaseTime *time)
{
	Int32 i;

	if (info.in_values)
	{
		for (i = 0; i < info.nr_of_in_values; ++i)
		{
			if (info.in_values[i])
			{
				if (!info.in_values[i]->Calculate(bn, GV_PORT_INPUT, run, calc, singleport, time)) return false;
			}
		}
	}
	return true;
}

Bool GvBuildOutPortsTable(GvNode *bn, GvPort **&ports, Int32 &nr_of_ports)
{
	Int32 i, j = bn->GetOutPortCount();
	if (!j) { ports = nullptr; return true; }
	ports = bNewDeprecatedUseArraysInstead<GvPort*>(j); if (!ports) goto error;
	for (i = 0; i < j; ++i)
	{
		ports[i] = bn->GetOutPort(i); if (!ports[i]) goto error;
	}
	nr_of_ports = j;
	return true;

error:
	bDelete(ports);
	nr_of_ports = 0;
	return false;
}

////////////////////////////////

GvWorld* GvGetWorld(void)
{
	return C4DOS.Gv->globals->GetWorld();
}

const	String GvGetEmptyString(void)
{
	return C4DOS.Gv->globals->GetEmptyString();
}

const String GvGetErrorString(const String &command, Int32 err)
{
	return C4DOS.Gv->globals->GetErrorString(command, err);
}

void GvGetPortList(GvPortsDescInfo *info, GvPortIO port, GvPortList &portlist)
{
	C4DOS.Gv->globals->GetPortList(info, port, portlist);
}

Bool GvGetAllDataTypes(GvPortDescInfo *info, UInt32 default_flag, Int32 first_id)
{
	return C4DOS.Gv->globals->GetAllDataTypes(info, default_flag, first_id);
}

void GvFreePortDescInfo(GvPortDescInfo *info)
{
	if (C4DOS.Gv->globals->FreePortDescInfo) C4DOS.Gv->globals->FreePortDescInfo(info);
}

Bool GvRegisterValueType(GV_VALUE_HANDLER *data, Int32 struct_size)
{
	if (!C4DOS.Gv->globals || !C4DOS.Gv->globals->RegisterValueType) return false;
	return C4DOS.Gv->globals->RegisterValueType(data, struct_size);
}

Bool GvRegisterDataType(GV_DATA_HANDLER *data, Int32 struct_size, const char *symbol)
{
	if (!C4DOS.Gv->globals || !C4DOS.Gv->globals->RegisterDataType) return false;
	return C4DOS.Gv->globals->RegisterDataType(data, struct_size, symbol);
}

Bool GvRegisterValGroupType(GV_VALGROUP_HANDLER *data, Int32 struct_size)
{
	if (!C4DOS.Gv->globals || !C4DOS.Gv->globals->RegisterValGroupType) return false;
	return C4DOS.Gv->globals->RegisterValGroupType(data, struct_size);
}

Bool GvRegisterOpClassType(GV_OPCLASS_HANDLER *data, Int32 struct_size)
{
	if (!C4DOS.Gv->globals || !C4DOS.Gv->globals->RegisterOpClassType) return false;
	return C4DOS.Gv->globals->RegisterOpClassType(data, struct_size);
}

Bool GvRegisterOpGroupType(GV_OPGROUP_HANDLER *data, Int32 struct_size)
{
	if (!C4DOS.Gv->globals || !C4DOS.Gv->globals->RegisterOpGroupType) return false;
	return C4DOS.Gv->globals->RegisterOpGroupType(data, struct_size);
}

GV_OPCLASS_HANDLER* GvFindRegisteredOpClass(GvOpClassID id)
{
	return C4DOS.Gv->globals->FindRegisteredOpClass(id);
}

GV_OPGROUP_HANDLER* GvFindRegisteredOpGroup(GvOpGroupID id)
{
	return C4DOS.Gv->globals->FindRegisteredOpGroup(id);
}

////////////////////////////////
