#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include "operatingsystem.h"
#include "c4d_general.h"
#include "c4d_network.h"
#include "c4d_basecontainer.h"

NetworkIpAddrPort NetworkIpConnection::GetRemoteAddr() const
{
	return IpCall(GetRemoteAddr)();
}

Int64 NetworkIpConnection::GetTransferedBytes() const
{
	return C4DOS.Ne->NetworkIpConnectionGetTransferedBytes(this);
}

NetworkIpAddrPort NetworkIpConnection::GetHostAddr() const
{
	return IpCall(GetHostAddr)();
}

// only for inherited sdk init!
NetworkIpAddr::NetworkIpAddr(_DONTCONSTRUCT v)
{
}

NetworkIpAddr::NetworkIpAddr()
{
	IpCall(SDKAlloc)();
}

NetworkIpAddr::NetworkIpAddr(const NetworkIpAddr& a)
{
	IpCall(SDKAlloc2)(a);
}

NetworkIpAddr::NetworkIpAddr(UChar a, UChar b, UChar c, UChar d)
{
	IpCall(SDKAlloc)();
	IpCall(SetIPv4)(a, b, c, d);
}

NetworkIpAddr::NetworkIpAddr(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8)
{
	IpCall(SDKAlloc)();
	IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

NetworkIpAddr::~NetworkIpAddr()
{
	IpCall(SDKFree)();
}

NetworkIpAddrPort::~NetworkIpAddrPort()
{
	IpCall(SDKFree)();
}

void NetworkIpAddr::Flush()
{
	IpCall(Flush)();
}

Bool NetworkIpAddr::SetIPv4(UChar a, UChar b, UChar c, UChar d)
{
	return IpCall(SetIPv4)(a, b, c, d);
}

Bool NetworkIpAddr::IsValid() const
{
	return IpCall(IsValid1)();
}

Bool NetworkIpAddr::SetIPv6(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8)
{
	return IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

Bool NetworkIpAddr::GetIPv4(UChar& a, UChar& b, UChar& c, UChar& d) const
{
	return IpCall(GetIPv4)(a, b, c, d);
}

Bool NetworkIpAddr::GetIPv6(Int16& x1, Int16& x2, Int16& x3, Int16& x4, Int16& x5, Int16& x6, Int16& x7, Int16& x8) const
{
	return IpCall(GetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

Bool NetworkIpAddr::IsPrivateAddress() const
{
	return IpCall(IsPrivateAddress)();
}

Bool NetworkIpAddr::CopyTo(NetworkIpAddr& adr) const
{
	return IpCall(CopyTo)(adr);
}

Bool NetworkIpAddr::IsEmpty() const
{
	return IpCall(IsEmpty)();
}

Bool NetworkIpAddr::Write(HyperFile* hf) const
{
	return IpCall(Write)(hf);
}

Bool NetworkIpAddr::Read(HyperFile* hf)
{
	return IpCall(Read)(hf);
}

Bool NetworkIpAddr::Compare(const NetworkIpAddr& adr) const
{
	return IpCall(Compare)(adr);
}

String NetworkIpAddr::GetString(Int32 port) const
{
	return IpCall(GetString)(port);
}

PROTOCOL NetworkIpAddr::GetProtocol() const
{
	return IpCall(GetProtocol)();
}

const NetworkIpAddrPort NetworkIpAddr::operator +(Int32 port) const
{
	return NetworkIpAddrPort(*this, port);
}

const NetworkIpAddr& NetworkIpAddr::operator =(const NetworkIpAddr& source)
{
	source.CopyTo(*this);
	return *this;
}

NetworkIpAddrPort::NetworkIpAddrPort() : NetworkIpAddr(DC)
{
	IpCall(SDKAllocPort)();
}

NetworkIpAddrPort::NetworkIpAddrPort(const NetworkIpAddr& a, Int32 port) : NetworkIpAddr(DC)
{
	IpCall(SDKAllocPort2)(a, port);
}

NetworkIpAddrPort::NetworkIpAddrPort(UChar a, UChar b, UChar c, UChar d, Int32 port) : NetworkIpAddr(DC)
{
	IpCall(SDKAllocPort)();
	IpCall(SetIPv4)(a, b, c, d);
	IpCall(SetPort)(port);
}

NetworkIpAddrPort::NetworkIpAddrPort(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8, Int32 port)
{
	IpCall(SDKAllocPort)();
	IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
	IpCall(SetPort)(port);
}

Bool NetworkIpAddrPort::Write(HyperFile* hf) const
{
	return IpCall(WriteAP)(hf);
}

Bool NetworkIpAddrPort::Read(HyperFile* hf)
{
	return IpCall(ReadAP)(hf);
}

void NetworkIpAddrPort::Flush()
{
	IpCall(Flush2)();
}

Bool NetworkIpAddrPort::IsValid() const
{
	return IpCall(IsValid2)();
}

String NetworkIpAddrPort::GetString(Bool port) const
{
	return IpCall(GetStringAP)(port);
}

void NetworkIpAddrPort::SetPort(Int32 port)
{
	IpCall(SetPort)(port);
}

Int32 NetworkIpAddrPort::GetPort() const
{
	return IpCall(GetPort)();
}

Bool NetworkIpAddrPort::operator ==(const NetworkIpAddrPort& a) const
{
	return IpCall(CompareAP)(a);
}

Bool NetworkIpAddrPort::operator !=(const NetworkIpAddrPort& a) const
{
	return !IpCall(CompareAP)(a);
}

Bool NetworkIpAddrPort::CopyTo(NetworkIpAddrPort& dst) const
{
	return IpCall(CopyTo2)(dst);
}

Int NetworkInterface::GetInterfaceIndex() const
{
	return IpCall(GetInterfaceIndex) ();
}

const NetworkIpAddrPort& NetworkIpAddrPort::operator =(const NetworkIpAddrPort& source)
{
	source.CopyTo(*this);
	return *this;
}

String NetworkInterface::GetInterfaceName() const
{
	return IpCall(GetInterfaceName) ();
}

void NetworkInterface::GetMacAddress(maxon::BaseArray<UChar>& macAddress) const
{
	return IpCall(GetMacAddress) (macAddress);
}

String NetworkInterface::GetDescription() const
{
	return IpCall(GetDescription) ();
}

Int NetworkInterface::GetCountAddress() const
{
	return IpCall(GetCountAddress) ();
}

Bool NetworkInterface::IsLoopback() const
{
	return IpCall(IsLoopback) ();
}

NetworkIpAddr NetworkInterface::GetIpAddress(Int i) const
{
	return IpCall(GetIpAddress) (i);
}

NetworkIpAddr NetworkInterface::GetBroadcastAddress(Int i) const
{
	return IpCall(GetBroadcastAddress) (i);
}

Bool NetworkInterface::Append(const NetworkIpAddr& ipAddr, const NetworkIpAddr& broadcastAddress, const NetworkIpAddr& subnetMask)
{
	return IpCall(Append) (ipAddr, broadcastAddress, subnetMask);
}

NetworkIpAddr NetworkInterface::GetSubnetMask(Int i) const
{
	return IpCall(GetSubnetMask) (i);
}

NetworkInterface* NetworkInterface::GetClone() const
{
	return IpCall(NetworkInterfaceGetClone) ();
}

Bool NetworkInterface::CopyTo(NetworkInterface& networkInterface) const
{
	return IpCall(NetworkInterfaceCopyTo) (networkInterface);
}

BaseContainer NetworkInterface::GetCustomData() const
{
	return IpCall(GetCustomData) ();
}

void NetworkInterface::SetCustomData(const BaseContainer& customData)
{
	return IpCall(SetCustomData) (customData);
}

Bool NetworkInterface::Write(HyperFile* hf) const
{
	return IpCall(NetworkInterfaceWrite) (hf);
}

Bool NetworkInterface::Read(HyperFile* hf)
{
	return IpCall(NetworkInterfaceRead) (hf);
}

NetworkIpConnection*	OpenListener(const NetworkIpAddrPort& adr, BaseThread* thread, Int sessionTimeout, Bool useNagleAlgorithm, Int* ferr)
{
	return NetCall(IpOpenListener) (adr, thread, sessionTimeout, useNagleAlgorithm, ferr);
}

NetworkIpConnection* OpenListener(const String& adr, BaseThread* thread, Int sessionTimeout, Bool useNagleAlgorithm, Int* ferr)
{
	return NetCall(IpOpenListenerString) (adr, thread, sessionTimeout, useNagleAlgorithm, ferr);
}

ZeroConfBrowser* StartZeroConfBrowser(const String& serviceType, ZeroConfBrowserCallback browseCallback, ZeroConfBrowserResolvedCallback resolveCallback, void* context)
{
	return NetCall(StartZeroConfBrowser) (serviceType, browseCallback, resolveCallback, context, true);
}

Bool GetBonjourVersion(Int& versionNumber, Int& revisionNumber, Bool& isRunning)
{
	return NetCall(GetBonjourVersion) (versionNumber, revisionNumber, isRunning);
}

void StopZeroConfBrowser(ZeroConfBrowser* browser)
{
	return NetCall(StopZeroConfBrowser) (browser);
}

ZeroConfService* RegisterZeroConfService(String serviceName, const String& serviceType, Int lInterface, Int32 port, const String& domainName)
{
	return NetCall(RegisterZeroConfService) (serviceName, serviceType, lInterface, port, domainName, true);
}

void DeregisterZeroConfService(ZeroConfService* service)
{
	NetCall(DeregisterZeroConfService) (service);
}

Bool ZeroConfService::SetTXTRecord(const String* keys, const String* values, Int cnt)
{
	return NetCall(SetTXTRecord) (this, keys, values, cnt);
}

Bool ZeroConfService::RemoveTXTRecord()
{
	return NetCall(RemoveTXTRecord) (this);
}

Bool WakeOnLan(const maxon::BaseArray<UChar>& macAddress, const NetworkIpAddr& broadcast)
{
	return NetCall(WakeOnLan) (macAddress, broadcast);
}

Bool GetMacAddress(maxon::BaseArray<UChar>& macAddress)
{
	return NetCall(GetMacAddress2) (macAddress);
}

String GetHostname()
{
	return NetCall(GetHostname)();
}

String GetHostname(const NetworkIpAddr& ipAddr)
{
	return NetCall(GetHostname2)(ipAddr);
}

Int GetInterfaceIndex(const String& identifier)
{
	return NetCall(GetInterfaceIndex2) (identifier);
}

Bool GetAllNetworkInterfaces(maxon::BaseArray<NetworkInterface*>& networkInterfaces)
{
	return NetCall(GetAllNetworkInterfaces) (networkInterfaces);
}

NetworkInterface* GetBestNetworkInterface(PROTOCOL protocol)
{
	return NetCall(GetBestNetworkInterface) (protocol);
}

NetworkIpConnection*	OpenWaitForIncoming(NetworkIpConnection* listener, BaseThread* connection, Int* error)
{
	return NetCall(IpWaitForIncoming) (listener, connection, error);
}

NetworkIpConnection* OpenOutgoing(const NetworkIpAddrPort& adr, BaseThread* thread, Int connectTimeout, Int sessionTimeout, Bool useNagleAlgorithm, Int* error)
{
	return NetCall(IpOpenOutgoing) (adr, thread, connectTimeout, sessionTimeout, useNagleAlgorithm, error);
}

NetworkIpConnection* OpenOutgoing(const String& adr, BaseThread* thread, Int connectTimeout, Int sessionTimeout, Bool useNagleAlgorithm, Int* error)
{
	return NetCall(IpOpenOutgoingString) (adr, thread, connectTimeout, sessionTimeout, useNagleAlgorithm, error);
}

RESOLVERESULT ResolveHostname(const String& address, PROTOCOL protocol, maxon::BaseArray<NetworkIpAddr>& addrs, Bool firstMatch, Bool forceResolve)
{
	return NetCall(ResolveHostname) (address, protocol, addrs, firstMatch, forceResolve);
}

Bool SplitAddress(String address, String* scheme, String* host, Int32* port)
{
	return NetCall(SplitAddress) (address, scheme, host, port);
}

Bool GetIpAddress(const String& address, NetworkIpAddr& a, Bool resolve, Bool forceResolve)
{
	return NetCall(GetIpAddress2) (address, a, resolve, forceResolve);
}

Bool GetIpAddress(const String& address, NetworkIpAddrPort& a, Bool resolve, Bool forceResolve)
{
	return NetCall(GetIpAddress3) (address, a, resolve, forceResolve);
}

void CloseConnection(NetworkIpConnection*& ipc)
{
	if (ipc)
		NetCall(IpCloseConnection) (ipc);
	ipc = nullptr;
}

void KillConnection(NetworkIpConnection*& ipc)
{
	NetCall(IpKillConnection) (ipc);
}

Int BytesInInputBuffer(NetworkIpConnection* ipc)
{
	return NetCall(IpBytesInInputBuffer) (ipc);
}

Int RecvBytes(NetworkIpConnection* ipc, void* buf, Int size)
{
	return NetCall(IpReadBytes) (ipc, buf, size);
}

Int SendBytes(NetworkIpConnection* ipc, const void* buf, Int size)
{
	return NetCall(IpSendBytes) (ipc, (void*)buf, size);
}
