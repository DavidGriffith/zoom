//
//  ZoomMetadata.m
//  ZoomCocoa
//
//  Created by Andrew Hunter on Tue Jan 13 2004.
//  Copyright (c) 2004 Andrew Hunter. All rights reserved.
//

#import "ZoomMetadata.h"

#include "ifmetadata.h"

@implementation ZoomMetadata

// = Initialisation, etc =

- (id) init {
	self = [super init];
	
	if (self) {
		metadata = malloc(sizeof(IFMetadata));
		
		metadata->numberOfStories = 0;
		metadata->numberOfErrors = 0;
		metadata->numberOfIndexEntries = 0;
		
		metadata->stories = NULL;
		metadata->error   = NULL;
		metadata->index   = NULL;
	}
	
	return self;
}

- (id) initWithContentsOfFile: (NSString*) filename {
	return [self initWithData: [NSData dataWithContentsOfFile: filename]];
}

- (id) initWithData: (NSData*) xmlData {
	self = [super init];
	
	if (self) {
		metadata = IFMD_Parse([xmlData bytes], [xmlData length]);
	}
	
	return self;
}

- (void) dealloc {
	IFMD_Free(metadata);
	
	[super dealloc];
}

// = Finding information =

- (ZoomStory*) findStory: (ZoomStoryID*) ident {
	IFMDStory* story;
	
	story = IFMD_Find(metadata, [ident ident]);
	
	if (story) {
		ZoomStory* res = [[ZoomStory alloc] initWithStory: story];
		
		return [res autorelease];
	} else {
		return nil;
	}
}

// = Storing information =
- (void) storeStory: (ZoomStory*) story {
	IFMD_AddStory(metadata, [story story]);
}

// = Saving the file =
static int dataWrite(const char* bytes, int length, void* userData) {
	NSMutableData* data = userData;
	[data appendBytes: bytes
			   length: length];
	return 0;
}

- (NSData*) xmlData {
	NSMutableData* res = [[NSMutableData alloc] init];
	
	IFMD_Save(metadata, dataWrite, res);
	
	return [res autorelease];
}

- (BOOL) writeToFile: (NSString*)path
		  atomically: (BOOL)flag {
	return [[self xmlData] writeToFile: path atomically: flag];
}

@end
