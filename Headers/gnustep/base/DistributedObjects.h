/* Interface internal use by Distributed Objects components
   Copyright (C) 1997 Free Software Foundation, Inc.

   Written by:  Richard Frith-Macdonald <richard@brainstorm.co.uk>
   Date: August 1997

   This file is part of the GNUstep Base Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
   */

#ifndef __DistributedObjects_h
#define __DistributedObjects_h

/*
 *	Changes from GNU DO to OPENSTEP style DO
 *
 *	Classes should implement [-classForPortCoder] instead of the old
 *	[-classForConnectedCoder] to return the class that should be sent
 *	over the wire.
 *
 *	Classes should implement [-replacementObjectForPortCoder:] instead of
 *	[+encodeObject:withConnectedCoder:] to encode objects.
 *	The default action is to send a proxy.
 */

#include <Foundation/NSConnection.h>
#include <Foundation/NSDistantObject.h>
#include <Foundation/NSPortCoder.h>

@class	InPacket;

@class	NSDistantObject;
@class	NSConnection;
@class	NSPort;
@class	PortDecoder;
@class	PortEncoder;

/*
 *	Distributed Objects identifiers
 *	These define the type of messages sent by the D.O. system.
 */
enum {
 METHOD_REQUEST = 0,
 METHOD_REPLY,
 ROOTPROXY_REQUEST,
 ROOTPROXY_REPLY,
 CONNECTION_SHUTDOWN,
 METHODTYPE_REQUEST,	/* these two only needed with NeXT runtime */
 METHODTYPE_REPLY,	/* these two only needed with NeXT runtime */
 PROXY_RELEASE,
 PROXY_RETAIN,
};


/*
 *	Catagory containing the methods by which the public interface to
 *	NSConnection must be extended in order to allow it's use by
 *	by NSDistantObject et al for implementation of Distributed objects.
 */
@interface NSConnection (Internal)
+ (NSConnection*) connectionByInPort: (NSPort*)ip
			     outPort: (NSPort*)op;
+ (NSConnection*) connectionByOutPort: (NSPort*)op;
- (NSDistantObject*) localForTarget: (void*)target;
- (NSDistantObject*) proxyForTarget: (void*)target;
- (void) retainTarget: (unsigned)target;
- (void) setNotOwned;
@end


/*
 *	Catagory containing the methods by which the public interface to
 *	NSPortCoder must be extended in order to allow it's use by
 *	by NSConnection et al for implementation of Distributed objects.
 */
@interface NSPortCoder (Internal)

+ newDecodingWithPacket: (InPacket*)packet
	     connection: (NSConnection*)c;

+ newDecodingWithConnection: (NSConnection*)c
		    timeout: (int) timeout;

+ newForWritingWithConnection: (NSConnection*)c
	       sequenceNumber: (int)n
		   identifier: (int)i;

- (void) dismiss;
- (unsigned) sequenceNumber;
- (int) identifier;
- (NSPort*) replyPort;

@end

#endif /* __DistributedObjects_h */
