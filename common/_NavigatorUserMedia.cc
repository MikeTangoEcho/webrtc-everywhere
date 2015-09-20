/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#navigatorusermedia
#include "_NavigatorUserMedia.h"
#include "_MediaStream.h"
#include "_MediaStreamTrack.h"
#include "_MediaTrackConstraints.h"
#include "_MediaStreamConstraints.h"
#include "_Utils.h"
#include "_Debug.h"

#include "talk/app/webrtc/videosourceinterface.h"
#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/media/devices/devicemanager.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/logging.h"

// void getUserMedia (MediaStreamConstraints? constraints, NavigatorUserMediaSuccessCallback successCallback, NavigatorUserMediaErrorCallback errorCallback);
void _NavigatorUserMedia::getUserMedia(const _MediaStreamConstraints* constraints/*= NULL*/, _NavigatorUserMediaSuccessCallback successCallback/*= nullPtr*/, _NavigatorUserMediaErrorCallback errorCallback /*= nullPtr*/)
{
#define RAISE_ERR(e) { \
		WE_DEBUG_ERROR(e); \
		if (errorCallback) { \
			cpp11::shared_ptr<_NavigatorUserMediaError> err(new _NavigatorUserMediaError(e)); \
			errorCallback(err); \
				} \
	}

#if WE_UNDER_WINDOWS
	// On windows, when the plugin is loaded a second time ThreadManager lose the current Thread pointer.
	// Then we have a crash on VideoCapturer.CaptureState because thread_ = NULL
	if (!rtc::Thread::Current()){
		rtc::ThreadManager::Instance()->SetCurrentThread(_Utils::GetWin32Thread());
	}
#endif

	cpp11::shared_ptr<_MediaStream> stream(new _MediaStream());
	if (!stream) {
		RAISE_ERR("Failed to create media stream");
		return;
	}

	bool bHaveAudio = !constraints || !constraints->audio() || !constraints->audio()->isBool() || constraints->audio()->boolVal();
	bool bHaveVideo = !constraints || !constraints->video() || !constraints->video()->isBool() || constraints->video()->boolVal();

	if (bHaveAudio) {
		_MediaStreamTrackAudio audio(NULL, constraints ? constraints->audio().get() : NULL);
		if (audio.IsValid()) {
			stream->addTrack(&audio);
		}
	}
	if (bHaveVideo) {
		_MediaStreamTrackVideo video(NULL, constraints ? constraints->video().get() : NULL);
		if (video.IsValid()) {
			stream->addTrack(&video);
		}
	}

	if (successCallback) {
		successCallback(stream);
	}
}

void _NavigatorUserMedia::getUserMedia(bool gumAsked /*= false*/, std::string audioSource /*= ""*/,	std::string videoSource /*= ""*/, const _MediaStreamConstraints* constraints/*= NULL*/, _NavigatorUserMediaSuccessCallback successCallback/*= nullPtr*/, _NavigatorUserMediaErrorCallback errorCallback /*= nullPtr*/)
{
#define RAISE_ERR(e) { \
		WE_DEBUG_ERROR(e); \
		if (errorCallback) { \
			cpp11::shared_ptr<_NavigatorUserMediaError> err(new _NavigatorUserMediaError(e)); \
			errorCallback(err); \
						} \
	}

#if WE_UNDER_WINDOWS
	// On windows, when the plugin is loaded a second time ThreadManager lose the current Thread pointer.
	// Then we have a crash on VideoCapturer.CaptureState because thread_ = NULL
	if (!rtc::Thread::Current()){
		rtc::ThreadManager::Instance()->SetCurrentThread(_Utils::GetWin32Thread());
	}
#endif

	cpp11::shared_ptr<_MediaStream> stream(new _MediaStream());
	if (!stream) {
		RAISE_ERR("Failed to create media stream");
		return;
	}

	bool bHaveAudio = !constraints || !constraints->audio() || !constraints->audio()->isBool() || constraints->audio()->boolVal();
	bool bHaveVideo = !constraints || !constraints->video() || !constraints->video()->isBool() || constraints->video()->boolVal();

	bHaveAudio = bHaveAudio && (!gumAsked || (gumAsked && audioSource != ""));
	bHaveVideo = bHaveVideo && (!gumAsked || (gumAsked && videoSource != ""));

	if (bHaveAudio) {
		_MediaStreamTrackAudio audio(audioSource, NULL, constraints ? constraints->audio().get() : NULL);
		if (audio.IsValid()) {
			stream->addTrack(&audio);
		}
	}
	if (bHaveVideo) {
		_MediaStreamTrackVideo video(videoSource, NULL, constraints ? constraints->video().get() : NULL);
		if (video.IsValid()) {
			stream->addTrack(&video);
		}
	}

	if (successCallback) {
		successCallback(stream);
	}
}
