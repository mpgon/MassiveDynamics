//////////////////////////////////////////////////////////////////////////
/// 
/// \file	MP3.cpp
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
//	Includes
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//	Includes 
//
//////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>
#include <uuids.h>
#include "MP3.h"

// force the DirectShow libs to be linked
#pragma comment(lib,"strmiids.lib")


/// used to build our 'media' graph that processes the file.
///	Essentually DirectShow will take something such as an mpeg
///	or mp3, and will split the file into a series of nodes
///	and connections. ie, two nodes may be created that represent the
///	left and right stereo sound channels, and an additional stereo
///	mixer control added for playback. 
/// 
///	This is very similar to the node layout of say the hypergraph
///	in Maya. Fortunately, DirectShow will build this graph for us.
///	If we wanted to, we could additional nodes such as filters or
///	Digital FX (ie reverb) to the sound, but thats not really part
///	of this basic example.
///
IGraphBuilder* g_pGraphBuilder = NULL;

/// used to control playback of the file. The level of control over
///	the specific Media file is determined by the interfaces to the
///	media that you request. For example, if we want to be able to 
///	start, pause and stop playback of the file, we need to get 
///	a pointer to an IMediaControl interface. If we want basic control
///	over things such as volume and panning, then we need to get a 
///	pointer to an IBasicAudio interface. We can choose which interfaces
///	to use, so it should be fairly easy to extend this code for other
///	purposes...
///
IMediaControl* g_pPlaybackControl = NULL;

/// provides a handle to basic volume and balance controls.
///
IBasicAudio*   g_pVolumeControl = NULL;

/// is the file ready for playback?
int			   g_bReady = 0;


//////////////////////////////////////////////////////////////////////////
/// \brief	ctor
///
void Mp3Init(void)
{
	CoInitialize(NULL);
}

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to pause playback of the mp3
/// \param	szFile	-	the name of the file to load
///
void Mp3Load(char filename[])
{
	// DirectShow requires unicode (16bit) characters rather than 8bit ascii
	WCHAR wFile[MAX_PATH];

	// convert ascii to unicode
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wFile, MAX_PATH);

	// create a graph build to allow us to make the audio signal path
	if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&g_pGraphBuilder)))
	{
		// create a simple controller for the sound file
		g_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&g_pPlaybackControl);

		// create a simple interface for volume and balance
		g_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void **)&g_pVolumeControl);

		// load and start playback of the specified sound file
		if (SUCCEEDED(g_pGraphBuilder->RenderFile(wFile, NULL)))
		{
			g_bReady = 1;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//	Functionality Given by the IMediaControl Interface

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
/// \brief	call this to start playback of the mp3
void Mp3Play(void)
{
	if (g_bReady)
	{
		g_pPlaybackControl->Run();
	}
}

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to stop playback of the mp3
void Mp3Stop(void)
{
	if (g_bReady)
	{
		g_pPlaybackControl->Stop();
	}
}

