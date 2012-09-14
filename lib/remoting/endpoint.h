/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef ENDPOINT_H
#define ENDPOINT_H

namespace icinga
{

class EndpointManager;

/**
 * An endpoint that can be used to send and receive messages.
 *
 * @ingroup icinga
 */
class I2_REMOTING_API Endpoint : public DynamicObject
{
public:
	typedef shared_ptr<Endpoint> Ptr;
	typedef weak_ptr<Endpoint> WeakPtr;

	typedef void (Callback)(const Endpoint::Ptr&, const Endpoint::Ptr&, const RequestMessage&);

	Endpoint(const Dictionary::Ptr& serializedUpdate);

	static bool Exists(const String& name);
	static Endpoint::Ptr GetByName(const String& name);

	String GetAddress(void) const;

	JsonRpcClient::Ptr GetClient(void) const;
	void SetClient(const JsonRpcClient::Ptr& client);

	void RegisterSubscription(const String& topic);
	void UnregisterSubscription(const String& topic);
	bool HasSubscription(const String& topic) const;

	Dictionary::Ptr GetSubscriptions(void) const;
	void SetSubscriptions(const Dictionary::Ptr& subscriptions);

	bool IsLocalEndpoint(void) const;
	bool IsConnected(void) const;

	void ProcessRequest(const Endpoint::Ptr& sender, const RequestMessage& message);
	void ProcessResponse(const Endpoint::Ptr& sender, const ResponseMessage& message);

	void ClearSubscriptions(void);

	void RegisterTopicHandler(const String& topic, const function<Callback>& callback);
	void UnregisterTopicHandler(const String& topic, const function<Callback>& callback);

	virtual void OnAttributeChanged(const String& name, const Value& oldValue);

	String GetNode(void) const;
	String GetService(void) const;

	static Endpoint::Ptr MakeEndpoint(const String& name, bool local);

	static boost::signal<void (const Endpoint::Ptr&)> OnConnected;
	static boost::signal<void (const Endpoint::Ptr&)> OnDisconnected;

	static boost::signal<void (const Endpoint::Ptr&, const String& topic)> OnSubscriptionRegistered;
	static boost::signal<void (const Endpoint::Ptr&, const String& topic)> OnSubscriptionUnregistered;

private:
	bool m_ReceivedWelcome; /**< Have we received a welcome message
				     from this endpoint? */
	bool m_SentWelcome; /**< Have we sent a welcome message to this
			         endpoint? */

	map<String, shared_ptr<boost::signal<Callback> > > m_TopicHandlers;

	void NewMessageHandler(const MessagePart& message);
	void ClientClosedHandler(void);
};

}

#endif /* ENDPOINT_H */