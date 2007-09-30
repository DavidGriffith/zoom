//
//  ZoomDownload.h
//  ZoomCocoa
//
//  Created by Andrew Hunter on 30/09/2007.
//  Copyright 2007 Andrew Hunter. All rights reserved.
//

#import <Cocoa/Cocoa.h>


///
/// Class that handles the download and unarchiving of files, such as plugin updates
///
@interface ZoomDownload : NSObject {
	NSURL* url;													// Where to download from
	id delegate;												// The download delegate
	
	NSURLConnection* connection;								// The connection that the download will be loaded via
	NSFileHandle* downloadFile;									// A file handle containing the file that we're downloading
	NSString* tmpFile;											// The file that the download is going to
	NSString* tmpDirectory;										// The directoruy that the download was unarchived to
	long long expectedLength;									// The expected length of the download
	long long downloadedSoFar;									// The amount downloaded so far
}

// Initialisation
- (id) initWithUrl: (NSURL*) url;								// Prepares to download the specified URL
- (void) setDelegate: (id) delegate;							// Sets the delegate for this class

// Starting the download
- (void) startDownload;											// Starts the download running

// Getting the download directory
- (NSURL*) url;													// The url for this download
- (NSString*) downloadDirectory;								// The temporary directory where the download was placed (deleted when this object is dealloced)

@end

///
/// Delegate methods for the download class
///
@interface NSObject(ZoomDownloadDelegate)

- (void) downloadStarting: (ZoomDownload*) download;			// A download is starting
- (void) downloadComplete: (ZoomDownload*) download;			// The download has completed
- (void) downloadFailed: (ZoomDownload*) download;				// The download failed for some reason

- (void) downloadConnecting: (ZoomDownload*) download;			// The download is connecting
- (void) downloading: (ZoomDownload*) download;					// The download is reading data
- (void) download: (ZoomDownload*) download						// Value between 0 and 1 indicating how far the download has progressed
		completed: (float) complete;
- (void) downloadUnarchiving: (ZoomDownload*) download;			// Indicates that a .zip or .tar file is being decompressed

@end
