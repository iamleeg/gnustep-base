/* Interface for NSURLAuthenticationChallenge for GNUstep
   Copyright (C) 2006 Software Foundation, Inc.

   Written by:  Richard Frith-Macdonald <frm@gnu.org>
   Date: 2006
   
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
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.
   */ 

#ifndef __NSURLAuthenticationChallenge_h_GNUSTEP_BASE_INCLUDE
#define __NSURLAuthenticationChallenge_h_GNUSTEP_BASE_INCLUDE

#include <Foundation/NSObject.h>

#if OS_API_VERSION(100200,GS_API_LATEST) && GS_API_VERSION(011300,GS_API_LATEST)

@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLCredential;
@class NSURLProtectionSpace;
@class NSURLResponse;

/**
 */
@protocol NSURLAuthenticationChallengeSender <NSObject>

/**
 */
- (void) cancelAuthenticationChallenge:
  (NSURLAuthenticationChallenge *)challenge;

/**
 */
- (void) continueWithoutCredentialForAuthenticationChallenge:
  (NSURLAuthenticationChallenge *)challenge;

/**
 */
- (void) useCredential: (NSURLCredential *)credential
  forAuthenticationChallenge: (NSURLAuthenticationChallenge *)challenge;

@end


/**
 * Class to represent an authentication challenge and indicate when the
 * challenge is complete.
 */
@interface NSURLAuthenticationChallenge : NSObject
{
@private
  void	*_NSURLAuthenticationChallengeInternal;
}

/**
 * Returns the error with which the reciver was initialised or nil
 * if it was not initialised with an error.<br />
 * The error may indicate the nature of the authentication failure.
 */
- (NSError *) error;

/**
 * Returns the response with which the receiver was initialised.<br />
 * This response contains the authentication failure corresponding to
 * this challenge object.<br />
 * If there was no failure or response, returns nil.
 */
- (NSURLResponse *) failureResponse;

/**
 * Initialises a new challenge by copying information from an old one.
 */
- (id) initWithAuthenticationChallenge:
  (NSURLAuthenticationChallenge *)challenge
				sender:
  (id<NSURLAuthenticationChallengeSender>)sender;

/**
 * Returns the receiver initialised in the specified protection space and
 * with the specified credential.  The previousFailureCount says how many
 * requests have failed the challenge and response provide information
 * about the last failure (which caused this challenge to be created).<br />
 * The error provides information about the authentication failure and
 * the sender is the object to receive callbacks.
 */
- (id) initWithProtectionSpace: (NSURLProtectionSpace *)space
	    proposedCredential: (NSURLCredential *)credential
	  previousFailureCount: (int)previousFailureCount
	       failureResponse: (NSURLResponse *)response
			 error: (NSError *)error
			sender: (id<NSURLAuthenticationChallengeSender>)sender;

/**
 * Returns the count of failed authentication attempts.
 */
- (int) previousFailureCount;

/**
 * Returns a proposed credential to answer the challenge.<br />
 * If there is no credential available, this returns nil.<br />
 * The credential may come from storage or from the URL itsself.
 */
- (NSURLCredential *) proposedCredential;

/**
 * Returns the protection space needing authentication.
 */
- (NSURLProtectionSpace *) protectionSpace;

/**
 * Returns the sender of the challenge ... the object to which callbacks
 * should be made while processing the challenge.
 */
- (id<NSURLAuthenticationChallengeSender>) sender;

@end

#endif
#endif