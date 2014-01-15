//////////////////////////////////////////////////////////////////////////
/// 
/// \file	MP3.h
/// \author	Rob Bateman
///	\brief	This file uses DirectShow to load and play an Mp3 file. Err, 
///			in fact, playback is not limited to just mp3's, but also :
/// 
///			*.avi
///			*.qt
///			*.mov
///			*.mpg
///			*.mpeg
///			*.m1v
///			*.wav
///			*.mpa
///			*.mp2
///			*.mp3
///			*.au
///			*.aif
///			*.aiff
///			*.snd
///			*.mid
///			*.midi
///			*.rmi
///			
///			The video formats will be sound only! I may impliment some
///			form of vieo feedback if pestered enough.....
/// 
///			You must ensure that you call Mp3Init() when your application
///			starts, and Mp3Cleanup() when your app finishes. 
/// 
///			In order to play an mp3 file, call the function Mp3Load()
///			specifying the name of the mp3 file to play.
/// 
///			You can then control playback with 
/// 
///			void Mp3Play()
///			void Mp3Pause()
///			void Mp3Stop()
/// 
///			You can set certain playback parameters with the functions :
/// 
///			void Mp3SetVolume(long)
///			long Mp3GetVolume()
///			void Mp3SetBalance(long)
///			long Mp3GetBalance()
/// 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//	Sentry  (prevents header being included twice)
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _MP3_PLAYER_H_
#define _MP3_PLAYER_H_

//////////////////////////////////////////////////////////////////////////
//
//	DirectShow Initialisation / Uninitialisation
//
//////////////////////////////////////////////////////////////////////////

/// \brief	You must call this function before calling any other Mp3 function
///
extern void Mp3Init(void);


//////////////////////////////////////////////////////////////////////////
//
//	Load an Mp3 File
//
//////////////////////////////////////////////////////////////////////////

/// \brief	this function loads the specified file for playback
/// \param	filename	-	the name of the file to load
///
extern void Mp3Load(char filename[]);


//////////////////////////////////////////////////////////////////////////
//
//	Mp3 Playback Controls
//
//////////////////////////////////////////////////////////////////////////


/// \brief	call this to start playback of the mp3
///
extern void Mp3Play(void);


/// \brief	call this to stop the playback of the mp3
///
extern void Mp3Stop(void);


#endif
