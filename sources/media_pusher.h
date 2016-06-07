#ifndef _MEDIA_PUSHER_H_
#define _MEDIA_PUSHER_H_

#include <string>

#include <xmedia.h>
#include <xfile.h>

#include "ts_muxer.h"

namespace flvpusher {

class RtmpHandler;

class MediaPusher {
public:
    MediaPusher(const std::string &input,
            RtmpHandler *&rtmp_hdl);
    virtual ~MediaPusher();

    virtual void ask2quit() { m_quit = true; }
    virtual int loop() = 0;

    int dump_video(const std::string &path);
    int dump_audio(const std::string &path);
    int mux2ts(const std::string &tspath);

    virtual int on_frame(const int32_t ts,
            const byte *dat, const uint32_t dat_len, int is_video);

protected:
    void set_itime_base(AVRational tb)
    { m_itime_base = tb; }

protected:
    std::string m_input;
    RtmpHandler *m_rtmp_hdl;
    volatile bool m_quit;

    std::string m_tspath;

private:
    xfile::File m_dvf;
    xfile::File m_daf;

    AVRational m_itime_base;
    TSMuxer m_tsmuxer;

    xutil::RecursiveMutex m_mutex;
};

}

#endif /* end of _MEDIA_PUSHER_H_ */
