/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_NETWORK_H__
#define C4D_NETWORK_H__

#ifndef __API_INTERN__
	#include "c4d_string.h"
	#include "c4d_basecontainer.h"
	#include "ge_prepass.h"
#else
	#include "ge_string.h"
#endif

#include "ge_math.h"
#ifdef USE_API_MAXON
	#include "maxon/basearray.h"
#else
	#include "c4d_misc/datastructures/basearray.h"
#endif

class NetworkIpAddrPort;
class ZeroConfTask;
class NetworkIpConnection;

#ifndef MAXON_TARGET_WINDOWS
	#define INVALID_SOCKET -1
#endif

#define NETWORK_INTERFACE_ANY	0

#ifndef AF_INET
	#define AF_INET 2			///< Internet protocol address family.
#endif

#ifndef AF_INET6
	#define AF_INET6 30			///< Internet protocol version @em 6 address family.
#endif

#define NetCall(fnc)	(*C4DOS.Ne->fnc)
#define IpCall(fnc)		(this->*C4DOS.Ne->fnc)

//----------------------------------------------------------------------------------------
/// Represents an IP address.
//----------------------------------------------------------------------------------------
class NetworkIpAddr
{
protected:
	explicit NetworkIpAddr(_DONTCONSTRUCT v);

public:
	/// @name Constructor/Destructor
	/// @{

	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr();

	//----------------------------------------------------------------------------------------
	/// Copy constructor.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr(const NetworkIpAddr& a);

	//----------------------------------------------------------------------------------------
	/// Constructs an IPv4 address.
	/// @param[in] a									First octet.
	/// @param[in] b									Second octet.
	/// @param[in] c									Third octet.
	/// @param[in] d									Fourth octet.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr(UChar a, UChar b, UChar c, UChar d);

	//----------------------------------------------------------------------------------------
	/// Constructs an IPv6 address.
	/// @param[in] x1									First hexadecimal digits group.
	/// @param[in] x2									Second hexadecimal digits group.
	/// @param[in] x3									Third hexadecimal digits group.
	/// @param[in] x4									Fourth hexadecimal digits group.
	/// @param[in] x5									Fifth hexadecimal digits group.
	/// @param[in] x6									Sixth hexadecimal digits group.
	/// @param[in] x7									Seventh hexadecimal digits group.
	/// @param[in] x8									Eighth hexadecimal digits group.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8);

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~NetworkIpAddr();

	/// @}

	/// @name Get/Set IPv4/IPv6
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets an IPv4 address.
	/// @param[out] a									Assigned first octet.
	/// @param[out] b									Assigned second octet.
	/// @param[out] c									Assigned third octet.
	/// @param[out] d									Assigned fourth octet.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetIPv4(UChar& a, UChar& b, UChar& c, UChar& d) const;

	//----------------------------------------------------------------------------------------
	/// Gets an IPv6 address.
	/// @param[out] x1								Assigned first hexadecimal digits group.
	/// @param[out] x2								Assigned second hexadecimal digits group.
	/// @param[out] x3								Assigned third hexadecimal digits group.
	/// @param[out] x4								Assigned fourth hexadecimal digits group.
	/// @param[out] x5								Assigned fifth hexadecimal digits group.
	/// @param[out] x6								Assigned sixth hexadecimal digits group.
	/// @param[out] x7								Assigned seventh hexadecimal digits group.
	/// @param[out] x8								Assigned eighth hexadecimal digits group.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetIPv6(Int16& x1, Int16& x2, Int16& x3, Int16& x4, Int16& x5, Int16& x6, Int16& x7, Int16& x8) const;

	//----------------------------------------------------------------------------------------
	/// Sets an IPv4 address.
	/// @param[in] a									First octet.
	/// @param[in] b									Second octet.
	/// @param[in] c									Third octet.
	/// @param[in] d									Fourth octet.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetIPv4(UChar a, UChar b, UChar c, UChar d);

	//----------------------------------------------------------------------------------------
	/// Sets an IPv6 address.
	/// @param[in] x1									First hexadecimal digits group.
	/// @param[in] x2									Second hexadecimal digits group.
	/// @param[in] x3									Third hexadecimal digits group.
	/// @param[in] x4									Fourth hexadecimal digits group.
	/// @param[in] x5									Fifth hexadecimal digits group.
	/// @param[in] x6									Sixth hexadecimal digits group.
	/// @param[in] x7									Seventh hexadecimal digits group.
	/// @param[in] x8									Eighth hexadecimal digits group.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetIPv6(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8);

	/// @}

	/// @name Write/Read/CopyTo
	/// @{

	//----------------------------------------------------------------------------------------
	/// Writes the IP address to a hyper file.
	/// @param[in] hf									The hyper file to write to. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Write(HyperFile* hf) const;

	//----------------------------------------------------------------------------------------
	/// Reads the IP address from a hyper file.
	/// @param[in] hf									The hyper file to read from. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Read(HyperFile* hf);

	//----------------------------------------------------------------------------------------
	/// Copies the IP address to @formatParam{dst}.
	/// @param[out] dst								The destination IP address.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyTo(NetworkIpAddr& dst) const;

	/// @}

	/// @name Miscellaneous
	/// @{


	//----------------------------------------------------------------------------------------
	/// Compares the IP address with @formatParam{adr}.
	/// @param[in] adr								An IP address.
	/// @return												@trueOtherwiseFalse{the addresses are equal}
	//----------------------------------------------------------------------------------------
	Bool Compare(const NetworkIpAddr& adr) const;

	//----------------------------------------------------------------------------------------
	/// Checks if the IP address is in a private address space.
	/// @return												@trueOtherwiseFalse{the IP address is private}
	//----------------------------------------------------------------------------------------
	Bool IsPrivateAddress() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the IP address is valid.
	/// @return												@trueOtherwiseFalse{the IP address is valid}
	//----------------------------------------------------------------------------------------
	Bool IsValid() const;

	//----------------------------------------------------------------------------------------
	/// Checks if the IP address is empty.
	/// @return												@trueOtherwiseFalse{the address is empty}
	//----------------------------------------------------------------------------------------
	Bool IsEmpty() const;

	//----------------------------------------------------------------------------------------
	/// Gets the IP address as a string, optionally with a port number.
	/// @param[in] port								The optional port number to format in the string.
	/// @return												The IP address as a string.
	//----------------------------------------------------------------------------------------
	String GetString(Int32 port = 0) const;

	//----------------------------------------------------------------------------------------
	/// Gets the protocol of the IP address.
	/// @return												The protocol of the IP address.
	//----------------------------------------------------------------------------------------
	PROTOCOL GetProtocol() const;

	//----------------------------------------------------------------------------------------
	/// Flushes the address.
	//----------------------------------------------------------------------------------------
	void Flush();

	/// @}

	/// @name Operators
	/// @{

	//----------------------------------------------------------------------------------------
	/// Assignment operator.
	/// @param[in] source							The IP address to assign.
	/// @return												The assigned IP address.
	//----------------------------------------------------------------------------------------
	const NetworkIpAddr& operator =(const NetworkIpAddr& source);

	//----------------------------------------------------------------------------------------
	/// Add operator. Adds a port number to the IP address.
	/// @param[in] port								The port number to add.
	/// @return												The IP address with the added @formatParam{port} number.
	//----------------------------------------------------------------------------------------
	const NetworkIpAddrPort operator +(Int32 port) const;

	//----------------------------------------------------------------------------------------
	/// Equality operator.
	/// @param[in] adr								The IP address to compare with.
	/// @return												@trueOtherwiseFalse{the IP addresses are equal}
	//----------------------------------------------------------------------------------------
	Bool operator ==(const NetworkIpAddr& adr) const
	{
		return Compare(adr);
	}

	//----------------------------------------------------------------------------------------
	/// Inequality operator.
	/// @param[in] adr								The IP address to compare with.
	/// @return												@trueOtherwiseFalse{the IP addresses are different}
	//----------------------------------------------------------------------------------------
	Bool operator !=(const NetworkIpAddr& adr) const
	{
		return !Compare(adr);
	}

	/// @}

private:
	C4D_RESERVE_PRIVATE_TYPE(Int, dummyForRef);
};

//----------------------------------------------------------------------------------------
/// Represents an IP address + port.
//----------------------------------------------------------------------------------------
class NetworkIpAddrPort : public NetworkIpAddr
{
	typedef NetworkIpAddr SUPER;

public:
	/// @name Constructor/Destructor
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor. Creates an IP address + port with default values.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort();

	//----------------------------------------------------------------------------------------
	/// Creates an IP address + port with the given IP address and port number.
	/// @param[in] a									The IP address.
	/// @param[in] port								The port number.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort(const NetworkIpAddr& a, Int32 port);

	//----------------------------------------------------------------------------------------
	/// Creates an IPv4 IpAddrPort.
	/// @param[in] a									First octet.
	/// @param[in] b									Second octet.
	/// @param[in] c									Third octet.
	/// @param[in] d									Fourth octet.
	/// @param[in] port								The port number.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort(UChar a, UChar b, UChar c, UChar d, Int32 port);

	//----------------------------------------------------------------------------------------
	/// Creates an IPv6 IpAddrPort.
	/// @param[in] x1									First hexadecimal digits group.
	/// @param[in] x2									Second hexadecimal digits group.
	/// @param[in] x3									Third hexadecimal digits group.
	/// @param[in] x4									Fourth hexadecimal digits group.
	/// @param[in] x5									Fifth hexadecimal digits group.
	/// @param[in] x6									Sixth hexadecimal digits group.
	/// @param[in] x7									Seventh hexadecimal digits group.
	/// @param[in] x8									Eighth hexadecimal digits group.
	/// @param[in] port								The port number.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8, Int32 port);

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~NetworkIpAddrPort();

	/// @}

	/// @name Write/Read/CopyTo
	/// @{

	//----------------------------------------------------------------------------------------
	/// Writes the IP address + port to a hyper file.
	/// @param[in] hf									The hyper file to write to. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Write(HyperFile* hf) const;

	//----------------------------------------------------------------------------------------
	/// Reads the IP address + port from a hyper file.
	/// @param[in] hf									The hyper file to read from. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Read(HyperFile* hf);

	//----------------------------------------------------------------------------------------
	/// Copies the IP address +port to @formatParam{dst}.
	/// @param[out] dst								The destination IP address + port.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyTo(NetworkIpAddrPort& dst) const;

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Flushes the address + port.
	/// @since R16
	//----------------------------------------------------------------------------------------
	void Flush();

	//----------------------------------------------------------------------------------------
	/// Gets the IP address +port as a string, optionally with the port number.
	/// @param[in] getPort						The IP address as a string.
	/// @return												@formatConstant{true} to format the port number in the address string (default).
	//----------------------------------------------------------------------------------------
	String GetString(Bool getPort = true) const;

	//----------------------------------------------------------------------------------------
	/// Checks if the IpAddrPort is valid.
	/// @return												@trueOtherwiseFalse{the IpAddrPort is valid}
	//----------------------------------------------------------------------------------------
	Bool IsValid() const;

	/// @}

	/// @name Set/Get Port
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the port number.
	/// @param[in] port								The port number.
	//----------------------------------------------------------------------------------------
	void SetPort(Int32 port);

	//----------------------------------------------------------------------------------------
	/// Gets the port number.
	/// @return												The port number.
	//----------------------------------------------------------------------------------------
	Int32 GetPort() const;

	/// @}

	/// @name Operators
	/// @{

	//----------------------------------------------------------------------------------------
	/// Assignment operator.
	/// @param[in] source							The IP address + port to assign.
	/// @return												The assigned IP address + port.
	//----------------------------------------------------------------------------------------
	const NetworkIpAddrPort& operator =(const NetworkIpAddrPort& source);

	//----------------------------------------------------------------------------------------
	/// Equality operator.
	/// @param[in] a									The IP address to compare with.
	/// @return												@trueOtherwiseFalse{the IP addresses + port are equal}
	//----------------------------------------------------------------------------------------
	Bool operator ==(const NetworkIpAddrPort& a) const;

	//----------------------------------------------------------------------------------------
	/// Inequality operator.
	/// @param[in] a									The IP address to compare with.
	/// @return												@trueOtherwiseFalse{the IP addresses +port are different}
	//----------------------------------------------------------------------------------------
	Bool operator !=(const NetworkIpAddrPort& a) const;

	/// @}

private:
};

class NetworkInterface
{
public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{network interface}
	/// @return												@allocReturn{network interface}
	//----------------------------------------------------------------------------------------
	static NetworkInterface* Alloc() { return NetCall(NetworkInterfaceAlloc) (); }

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{network interfaces}
	/// @param[in,out] p							@theToDestruct{network interface}
	//----------------------------------------------------------------------------------------
	static void Free(NetworkInterface*& p) { NetCall(NetworkInterfaceFree) (p); }

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the network interface index.
	/// @param[in] interfaceIndex			The network interface index to set.
	//----------------------------------------------------------------------------------------
	void SetInterfaceIndex(Int interfaceIndex);

	//----------------------------------------------------------------------------------------
	/// Gets the network interface index.
	/// @return												The network interface index.
	//----------------------------------------------------------------------------------------
	Int GetInterfaceIndex() const;

	//----------------------------------------------------------------------------------------
	/// Sets the network interface name.
	/// @param[in] interfaceName			The network interface name to set.
	//----------------------------------------------------------------------------------------
	void SetInterfaceName(const String& interfaceName);

	//----------------------------------------------------------------------------------------
	/// Gets the network interface name.
	/// @return												The network interface name.
	//----------------------------------------------------------------------------------------
	String GetInterfaceName() const;

	//----------------------------------------------------------------------------------------
	/// Gets the MAC address for the network interface.
	/// @param[out] macAddress				Assigned the MAC address.
	//----------------------------------------------------------------------------------------
	void GetMacAddress(maxon::BaseArray<UChar>& macAddress) const;

	//----------------------------------------------------------------------------------------
	/// Gets the network interface description.
	/// @return												The network interface description.
	//----------------------------------------------------------------------------------------
	String GetDescription() const;

	//----------------------------------------------------------------------------------------
	/// Sets the network interface description.
	/// @param[in] description				The network interface description.
	//----------------------------------------------------------------------------------------
	void SetDescription(const String& description);

	//----------------------------------------------------------------------------------------
	/// Check if the network interface is loopback.
	/// @return												@trueIfOtherwiseFalse{the network interface is loopback}
	//----------------------------------------------------------------------------------------
	Bool IsLoopback() const;

	//----------------------------------------------------------------------------------------
	/// Sets the network interface loopback.
	/// @param[in] isLoopback					@formatConstant{true} to set the network interface loopback, @formatConstant{false} to unset it.
	//----------------------------------------------------------------------------------------
	void SetLoopback(Bool isLoopback);

	//----------------------------------------------------------------------------------------
	/// Flushes the network interface.
	//----------------------------------------------------------------------------------------
	void Flush();

	//----------------------------------------------------------------------------------------
	/// Clones the network interface.
	/// @return												The cloned network interface, or @formatConstant{nullptr} if an error occurred. @callerOwnsPointed{network interface}
	//----------------------------------------------------------------------------------------
	NetworkInterface* GetClone() const;

	/// @}

	/// @name Address
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the number of addresses in the network interface.
	/// @return												The number of addresses in the network interface.
	//----------------------------------------------------------------------------------------
	Int GetCountAddress() const;

	//----------------------------------------------------------------------------------------
	/// Appends an IP address to the network interface.
	/// @param[in] ipAddr							The IP address.
	/// @param[in] broadcastAddress		The broadcast address.
	/// @param[in] subnetMask					The subnet mask.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Append(const NetworkIpAddr& ipAddr, const NetworkIpAddr& broadcastAddress, const NetworkIpAddr& subnetMask);

	//----------------------------------------------------------------------------------------
	/// Retrieves the IP address at index @formatParam{i} in the network interface.
	/// @param[in] i									The index for the address: @em 0 <= @formatParam{i} < GetCountAddress()
	/// @return												The IP address.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr GetIpAddress(Int i) const;

	//----------------------------------------------------------------------------------------
	/// Retrieves the broadcast address at index @formatParam{i} in the network interface.
	/// @param[in] i									The index for the broadcast address: @em 0 <= @formatParam{i} < GetCountAddress()
	/// @return												The broadcast address.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr GetBroadcastAddress(Int i) const;

	//----------------------------------------------------------------------------------------
	/// Gets the subnet mask at index @formatParam{i} in the network interface.
	/// @param[in] i									The index for the subnet mask: @em 0 <= @formatParam{i} < GetCountAddress()
	/// @return												The subnet mask.
	//----------------------------------------------------------------------------------------
	NetworkIpAddr GetSubnetMask(Int i) const;

	/// @}

	/// @name Write/Read/CopyTo
	/// @{

	//----------------------------------------------------------------------------------------
	/// Writes the network interface to a hyper file.
	/// @param[in] hf									The hyper file to write to. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Write(HyperFile* hf) const;

	//----------------------------------------------------------------------------------------
	/// Reads the network interface from a hyper file.
	/// @param[in] hf									The hyper file to read from. @callerOwnsPointed{hyper file}
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Read(HyperFile* hf);

	//----------------------------------------------------------------------------------------
	/// Copies the network interface.
	/// @param[out] networkInterface	The network interface to copy to.
	/// @return												@trueOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyTo(NetworkInterface& networkInterface) const;

	/// @}

	/// @name Custom Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the custom data for the network interface.
	/// @return												A container with the custom data.
	//----------------------------------------------------------------------------------------
	BaseContainer GetCustomData() const;

	//----------------------------------------------------------------------------------------
	/// Set the custom data for the network interface.
	/// @param[in] customData					A container with the custom data to set.
	//----------------------------------------------------------------------------------------
	void SetCustomData(const BaseContainer& customData);

	/// @}

private:
	NetworkInterface();
	~NetworkInterface();
};

class ZeroConfService
{
	ZeroConfService() {}
	~ZeroConfService() {}

public:
	Bool SetTXTRecord(const String* keys, const String* values, Int cnt);
	Bool RemoveTXTRecord();
};

class NetworkIpConnection
{
	NetworkIpConnection() {}
	~NetworkIpConnection() {}
public:
	//----------------------------------------------------------------------------------------
	/// Retrieves the remote IP address + port for the connection.
	/// @return												The remote IP address + port.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort GetRemoteAddr() const;

	//----------------------------------------------------------------------------------------
	/// Retrieves the host IP address + port for the connection.
	/// @return												The host IP address + port.
	//----------------------------------------------------------------------------------------
	NetworkIpAddrPort GetHostAddr() const;

	//----------------------------------------------------------------------------------------
	/// Gets the number of bytes transferred during the connection.
	/// @return												The number of transferred bytes.
	//----------------------------------------------------------------------------------------
	Int64 GetTransferedBytes() const;
};


//----------------------------------------------------------------------------------------
/// Wakes a computer up by WOL (Wake-On-LAN). Currently only IPv4 is supported.\n
/// To get WOL to work, a broadcast message on port @em 9 will be sent.
/// @param[in] macAddress					The mac address of the target machine.
/// @param[in] broadcast					The broadcast address where the message should be send to.
/// @return												@trueIfOtherwiseFalse{the WOL message was sent}
//----------------------------------------------------------------------------------------
Bool WakeOnLan(const maxon::BaseArray<UChar>& macAddress, const NetworkIpAddr& broadcast);

//----------------------------------------------------------------------------------------
/// Gets the mac address of the machine.
/// @param[out] macAddress				Assigned the mac address.
/// @return												@trueIfOtherwiseFalse{the mac address was retrieved successfully}
/// @note													If an error occurred, @formatConstant{false} is returned but then @formatParam{macAddress} is filled at least with a random-generated mac address.\n
///																The random-generated mac address will be changed after a restart of the host application.
//----------------------------------------------------------------------------------------
Bool GetMacAddress(maxon::BaseArray<UChar>& macAddress);

//----------------------------------------------------------------------------------------
/// Gets the best network interface to the specified protocol.
/// @param[in] protocol						The specified protocol: @enumerateEnum{PROTOCOL}
/// @return												The found network interface.
//----------------------------------------------------------------------------------------
NetworkInterface* GetBestNetworkInterface(PROTOCOL protocol = PROTOCOL_IPV4);

//----------------------------------------------------------------------------------------
/// Gets all current active network interface objects.
/// @param[out] networkInterfaces	Assigned all the network interfaces.
//----------------------------------------------------------------------------------------
Bool GetAllNetworkInterfaces(maxon::BaseArray<NetworkInterface*>& networkInterfaces);

//----------------------------------------------------------------------------------------
/// Gets the host name of the local machine.
/// @return												The host name.
//----------------------------------------------------------------------------------------
String GetHostname();

//----------------------------------------------------------------------------------------
/// Gets the host name of the given IP address @formatParam{ipAddr}.
/// @return												The host name. Can be empty if the address could not be resolved.
//----------------------------------------------------------------------------------------
String GetHostname(const NetworkIpAddr& ipAddr);

//----------------------------------------------------------------------------------------
/// Gets the interface index.
/// @param[in] interfaceName			The interface name. The interface name @em "all" returns @em 0.
/// @return												The interface index.
//----------------------------------------------------------------------------------------
Int GetInterfaceIndex(const String& interfaceName);

//----------------------------------------------------------------------------------------
/// Resolves a host name.\n
/// If the address object can be an IP address object, GetIpAddress(address, &addr, true) should be used instead.
/// @param[in] address						The host name to resolve.
/// @param[in] ptype							Pass @ref PROTOCOL_IPV4 if the result should just contain @em IPv4 addresses, same for @ref PROTOCOL_IPV6 with @em IPv6 address and @@ref PROTOCOL_ALL for all addresses.
/// @param[out] addrs							Assigned the addresses of the host name when the function succeeded.
/// @param[in] firstMatch					If @formatConstant{true} address array @formatParam{addrs} has a maximum size of @em 1.
/// @param[in] forceResolve				If @formatConstant{false} use the DNS cache if the address is a host name and already known. Pass @formatConstant{true} for an automatic mode.
/// @return												::RESOLVERESULT_OK on success, otherwise the resolve operation failed.
//----------------------------------------------------------------------------------------
RESOLVERESULT ResolveHostname(const String& address, PROTOCOL ptype, maxon::BaseArray<NetworkIpAddr>& addrs, Bool firstMatch = true, Bool forceResolve = false);

//----------------------------------------------------------------------------------------
/// Converts a host name, @em IPv4 or @em IPv6 address into an IP address object.\n
/// A port value in the address will be ignored.
/// When the resolve option is enabled, the call blocks and waits for the DNS system when the address is a host name. e.g:
///			- <i>Sebastians-Macbook-Pro.local</i> : DNS system used, call does block
///			- <i>192.168.10.1</i> : no DNS system used, call does not block.
/// @param[in] address						The IP address or host name. If the string is a host name, @formatParam{resolve} must be set to @formatConstant{true} otherwise the function fails.
/// @param[out] a									Assigned the IP address object.
/// @param[in] resolve						Pass @formatConstant{true} to resolve the address via the DNS system.
/// @param[in] forceResolve				Pass @formatConstant{true} to force resolve.
/// @return												@trueIfOtherwiseFalse{the IP address was retrieved successfully}
//----------------------------------------------------------------------------------------
Bool GetIpAddress(const String& address, NetworkIpAddr& a, Bool resolve = false, Bool forceResolve = false);

//----------------------------------------------------------------------------------------
/// Converts a host name, @em IPv4 or @em IPv6 address into an IP address object.\n
/// A port value in the address will be ignored.
/// When the @formatParam{resolve} option is enabled, the call blocks and waits for the DNS system when the address is a host name. e.g:
///			- <i>Sebastians-Macbook-Pro.local</i> : DNS system used, call does block
///			- <i>192.168.10.1</i> : no DNS system used, call does not block.
/// @param[in] address						The IP address or host name. If the string is a host name, @formatParam{resolve} must be set to @formatConstant{true} otherwise the function fails.
/// @param[out] a									Assigned the IP address object.
/// @param[in] resolve						Pass @formatConstant{true} to resolve the address via the DNS system.
/// @param[in] forceResolve				Pass @formatConstant{true} to force resolve.
/// @return												@trueIfOtherwiseFalse{the IP address was successfully retrieved}
//----------------------------------------------------------------------------------------
Bool GetIpAddress(const String& address, NetworkIpAddrPort& a, Bool resolve = false, Bool forceResolve = false);

//----------------------------------------------------------------------------------------
/// Splits a specified scheme with host name and port into its components.\n
/// Handle @em IPv4, @em IPv6 addresses and host names.
/// @param[in] address						The host name to split.
///		Can optionally contain a scheme, host and port. For instance:
///		- <i>"http://127.0.0.1:8080"</i>
///		- <i>"http://[AB:AB:AB:AB:AB:AB]:1234"</i>
///		- <i>"192.168.10.1"</i>
///		- <i>"Sebastians-Macbook-Pro.local:80"</i>
/// @param[out] scheme						Assigned the scheme. Can be empty if no scheme was found.
/// @param[out] host							Assigned the address/host name without port scheme and port number.
/// @param[out] port							Assigned the port. If no port was found @ref NOTOK is assigned.
/// @return												@trueIfOtherwiseFalse{the IP address was successfully split}
//----------------------------------------------------------------------------------------
Bool SplitAddress(String address, String* scheme, String* host, Int32* port);

//----------------------------------------------------------------------------------------
/// Opens a connection. Supports @em IPv4.
/// @param[in] adr								The destination address to connect to.
/// @param[in] thread							The thread to use for the connection. @callerOwnsPointed{thread}
/// @param[in] connectTimeout			The timeout in seconds for the initial connection.
/// @param[in] sessionTimeout			The timeout in seconds for receive and send operations.
/// @param[in] useNagleAlgorithm	Pass @formatConstant{true} to set the TCP/IP flag for @em TCP_NODELAY. For more information see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx.
/// @param[in] error							Assigned error status if the connection failed. A value different than @em 0 indicates failure.
/// @return												The IP connection object. Must be freed with CloseConnection(). @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
NetworkIpConnection* OpenOutgoing(const NetworkIpAddrPort& adr, BaseThread* thread = nullptr, Int connectTimeout = 30, Int sessionTimeout = 10, Bool useNagleAlgorithm = true, Int* error = nullptr);

//----------------------------------------------------------------------------------------
/// Opens a connection. Supports @em IPv4.
/// @param[in] adr								The destination address to connect to (@em IPv4 address or host name).
/// @param[in] thread							The thread to use for the connection. @callerOwnsPointed{thread}
/// @param[in] connectTimeout			The timeout in seconds for the initial connection.
/// @param[in] sessionTimeout			The timeout in seconds for receive and send operations.
/// @param[in] useNagleAlgorithm	Pass @formatConstant{true} to set the TCP/IP flag for @em TCP_NODELAY. For more information see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx.
/// @param[in] error							Assigned error status if the connection failed. A value different than @em 0 indicates failure.
/// @return												The IP connection object. Must be freed with CloseConnection(). @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
NetworkIpConnection* OpenOutgoing(const String& adr, BaseThread* thread = nullptr, Int connectTimeout = 30, Int sessionTimeout = 10, Bool useNagleAlgorithm = true, Int* error = nullptr);

//----------------------------------------------------------------------------------------
/// Checks how many bytes are in the input buffer of an IP connection.
/// @param[in] ipc								The IP connection to check. @callerOwnsPointed{NetworkIpConnection}
/// @return												The number of bytes in the input buffer.
//----------------------------------------------------------------------------------------
Int BytesInInputBuffer(NetworkIpConnection* ipc);

//----------------------------------------------------------------------------------------
/// Reads the bytes from the IP connection @formatParam{ipc} to @formatParam{buf}.
/// @param[in] ipc								The IP connection to read from. @callerOwnsPointed{NetworkIpConnection}
/// @param[in] buf								The buffer to read to. @callerOwnsPointed{buffer}
/// @param[in] size								The size of the buffer @formatParam{buf}.
/// @return												The number of bytes read.
//----------------------------------------------------------------------------------------
Int RecvBytes(NetworkIpConnection* ipc, void* buf, Int size);

//----------------------------------------------------------------------------------------
/// Sends the bytes from @formatParam{buf} to the IP connection @formatParam{ipc}.
/// @param[in] ipc								The IP connection to send the bytes to. @callerOwnsPointed{NetworkIpConnection}
/// @param[in] buf								The buffer to send from. @callerOwnsPointed{buffer}
/// @param[in] size								The size of the buffer @formatParam{buf}.
/// @return												The number of bytes sent.
//----------------------------------------------------------------------------------------
Int SendBytes(NetworkIpConnection* ipc, const void* buf, Int size);

//----------------------------------------------------------------------------------------
/// Opens an IP listener.
/// @param[in] adr								The IP address of the network interface to use for the listener.
/// @param[in] thread							The thread to use for the connection. @callerOwnsPointed{thread}
/// @param[in] sessionTimeout			The time after which the listener closes an unresponsive connection.
/// @param[in] dontwait						Pass @formatConstant{true} to set the TCP/IP flag for @em TCP_NODELAY. For more information see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx.
/// @param[in] error							Assigned error status if the connection failed. A value different than @em 0 indicates failure.
/// @return												The IP connection object for the listener. Must be freed with CloseConnection(). @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
NetworkIpConnection* OpenListener(const NetworkIpAddrPort& adr, BaseThread* thread, Int sessionTimeout, Bool dontwait, Int* error);

//----------------------------------------------------------------------------------------
/// Opens an IP listener.
/// @param[in] adr								The IP address of the network interface to use for the listener.
/// @param[in] thread							The thread to use for the connection. @callerOwnsPointed{thread}
/// @param[in] sessionTimeout			The time after which the listener closes an unresponsive connection.
/// @param[in] useNagleAlgorithm	Pass @formatConstant{true} to set the TCP/IP flag for @em TCP_NODELAY. For more information see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx.
/// @param[in] error							Assigned error status if the connection failed. A value different than @em 0 indicates failure.
/// @return												The IP connection object for the listener. Must be freed with CloseConnection(). @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
NetworkIpConnection* OpenListener(const String& adr, BaseThread* thread, Int sessionTimeout, Bool useNagleAlgorithm, Int* error);

//----------------------------------------------------------------------------------------
/// Waits for an incoming connection to listener.
/// @param[in] listener						The listener IP connection to wait for. Needs to be freed with GeIpCloseConnection(). @callerOwnsPointed{NetworkIpConnection}
/// @param[in] connection					The thread to use for the connection. @callerOwnsPointed{thread}
/// @param[in] error							Assigned error status if the connection failed. A value different than @em 0 indicates failure.
/// @return												The IP connection object for the waiting connection. Must be freed with CloseConnection(). @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
NetworkIpConnection* OpenWaitForIncoming(NetworkIpConnection* listener, BaseThread* connection, Int* error);

//----------------------------------------------------------------------------------------
/// Kills an IP connection.
/// @note Calls End() for the connection thread.
/// @param[in] ipc								The IP connection to kill. @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
void KillConnection(NetworkIpConnection*& ipc);

//----------------------------------------------------------------------------------------
/// Closes and frees an IP connection.
/// @param[in] ipc								The IP connection to close. Assigned @formatConstant{nullptr} afterward. @callerOwnsPointed{NetworkIpConnection}
//----------------------------------------------------------------------------------------
void CloseConnection(NetworkIpConnection*& ipc);

// ZeroConf API

//----------------------------------------------------------------------------------------
/// Get the version number of the bonjour version.
/// @param[out] versionNumber			The main version number of bonjour.
/// @param[out] revisionNumber		The revision number.
/// @param[out] isRunning					If the function returns false, isRunning can be true to indicate that the bonjour service is running but this process cannot connect to it.
///																This can happen if the process is blocked by a firewall to connect to 127.0.0.1/localhost.
/// @return												True if Bonjour is installed, otherwise false.
//----------------------------------------------------------------------------------------
Bool GetBonjourVersion(Int& versionNumber, Int& revisionNumber, Bool& isRunning);

//----------------------------------------------------------------------------------------
/// Registers a bonjour browser.
/// @param[in] serviceType				A bonjour name like "_netrender._tcp".
/// @param[in] browseCallback			The bonjour browser callback. It is triggered if a service was found.
/// @param[in] resolveCallback		The bonjour browser resolve callback. It is triggered if its corresponding address is resolved.
/// @param[in] context						A user data variable that is to be passed to the callbacks.
/// @return												The bonjour browser. @cinemaOwnsPointed{bonjour browser}
//----------------------------------------------------------------------------------------
ZeroConfBrowser* StartZeroConfBrowser(const String& serviceType, ZeroConfBrowserCallback browseCallback, ZeroConfBrowserResolvedCallback resolveCallback, void* context);

//----------------------------------------------------------------------------------------
/// Stops a bonjour browsing process started with StartZeroConfBrowser().
/// @param[in] browser						The bonjour browser to stop. @cinemaOwnsPointed{bonjour browser}
//----------------------------------------------------------------------------------------
void StopZeroConfBrowser(ZeroConfBrowser* browser);

//----------------------------------------------------------------------------------------
/// Register a bonjour service.
/// @param[in] serviceName				The service name, a human readable string.
/// @param[in] serviceType				A string like "_netrender._tcp" with "_{serviceName}._{protocol}".
/// @param[in] lInterface					The interface index where it is reachable.
/// @param[in] port								Used to set where the service is reachable.
/// @param[in] domainName					Should be empty.
/// @return												The bonjour browser. @cinemaOwnsPointed{bonjour browser}
//----------------------------------------------------------------------------------------
ZeroConfService* RegisterZeroConfService(String serviceName, const String& serviceType, Int lInterface, Int32 port, const String& domainName = String());

//----------------------------------------------------------------------------------------
/// Deregisters a bonjour service that was registered with RegisterZeroConfService().
/// @param[in] service						The bonjour service to deregister. @cinemaOwnsPointed{bonjour browser}
//----------------------------------------------------------------------------------------
void DeregisterZeroConfService(ZeroConfService* service);

#endif // C4D_NETWORK_H__
