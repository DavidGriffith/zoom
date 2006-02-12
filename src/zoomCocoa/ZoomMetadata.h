//
//  ZoomMetadata.h
//  ZoomCocoa
//
//  Created by Andrew Hunter on Tue Jan 13 2004.
//  Copyright (c) 2004 Andrew Hunter. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ZoomStory.h"
#import "ZoomStoryID.h"

// Cocoa interface to the C ifmetadata class
// Yes, Panther now has a SAX parser. No, I'm not using it: I need Jaguar support.
// (Plus I want to be able to port all of Zoom's backend to other platforms. Also,
// SAX is pretty slow)

@interface ZoomMetadata : NSObject {
	NSString* filename;
	struct IFMetadata* metadata;
	
	NSLock* dataLock;
}

// Initialisation
- (id) init;											// Blank metadata
- (id) initWithContentsOfFile: (NSString*) filename;	// Calls initWithData
- (id) initWithData: (NSData*) xmlData;					// Designated initialiser

// Information about the parse
- (NSArray*) errors;

// Retrieving information
- (ZoomStory*) findStory: (ZoomStoryID*) ident;
- (NSArray*)   stories;

// Storing information
- (void) storeStory: (ZoomStory*) story;
- (void) removeIdent: (ZoomStoryID*) ident;

// Saving the file
- (NSData*) xmlData;
- (BOOL)    writeToFile: (NSString*)path
			 atomically: (BOOL)flag;
- (BOOL) writeToDefaultFile;

@end
