/*
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __VIDEO_OPTIONS_H_
#define __VIDEO_OPTIONS_H_

#include "imageFormat.h"
#include "commandLine.h"

#include "URI.h"


/**
 * The videoOptions struct contains common settings that are used
 * to configure and query videoSource and videoOutput streams.
 * @ingroup video
 */
struct videoOptions
{
public:
    /**
     * Constructor using default options.
     */
    videoOptions();

    /**
     * The resource URI of the device, IP stream, or file/directory.
     * @see URI for details about accepted protocols and URI formats.
     */
    URI resource;

    /**
     * The width of the stream (in pixels).
     * This option can be set from the command line using `--input-width=N`
     * for videoSource streams, or `--output-width=N` for videoOutput streams.
     */
    uint32_t width;

    /**
     * The height of the stream (in pixels).
     * This option can be set from the command line using `--input-height=N`
     * for videoSource streams, or `--output-height=N` for videoOutput streams.
     */
    uint32_t height;

    /**
     * The framerate of the stream (the default is 30Hz).
     * This option can be set from the command line using `--input-rate=N` or `--output-rate=N`
     * for input and output streams, respectively. The `--framerate=N` option sets it for both.
     */
    float frameRate;

    /**
     * The encoding bitrate for compressed streams (only applies to video codecs like H264/H265).
     * For videoOutput streams, this option can be set from the command line using `--bitrate=N`.
     * @note the default bitrate for encoding output streams is 4Mbps (target VBR).
     */
    uint32_t bitRate;


    /**
     * resources: https://github.com/dusty-nv/jetson-utils/issues/68
     */

    /**
     * White balance modes.
     */
    enum WbMode
    {
        GST_NVCAM_WB_MODE_OFF = 0,			//(0): off
        GST_NVCAM_WB_MODE_AUTO,				//(1): auto
        GST_NVCAM_WB_MODE_INCANDESCENT,		//(2): incandescent
        GST_NVCAM_WB_MODE_FLUORESCENT, 		//(3): fluorescent
        GST_NVCAM_WB_MODE_WARM_FLUORESCENT,	//(4): warm-fluorescent
        GST_NVCAM_WB_MODE_DAYLIGHT, 		//(5): daylight
        GST_NVCAM_WB_MODE_CLOUDY_DAYLIGHT, 	//(6): cloudy-daylight
        GST_NVCAM_WB_MODE_TWILIGHT, 		//(7): twilight
        GST_NVCAM_WB_MODE_SHADE, 			//(8): shade
        GST_NVCAM_WB_MODE_MAN, 				//(9): manual
    };

    /**
     * White balance affects the color temperature of the photo
     * @note Default: auto
     */
    WbMode wbmode;

    /**
    * Property to adjust saturation value
     * Range: 0 - 2
    * @note Default: 1
    */
    float saturation;

    /**
     *  Property to adjust exposure time range in nanoseconds
        Use string with values of Exposure Time Range (low, high)
        eg: "34000 358733000"
     * @note Default: null
     */
    char* exposuretimerange;

    /**
     * Property to adjust gain range
     * Use string with values of Gain Time Range (low, high)
     * eg: "1 16"
     * @note Default: null
     */
    char* gainrange;

    /**
     * Property to adjust exposure compensation
     * @note Default: 0
     */
    float exposurecompensation;

    /**
     * Set or unset the auto exposure lock
     * @note Default: false
     */
    bool aelock;

    /**
     * Set or unset the auto white balance lock
     * @note Default: false
     */
    bool awblock;


    /**
     * The number of ring buffers used for threading.
     * This option can be set from the command line using `--num-buffers=N`.
     * @note the default number of ring buffers is 4.
     */
    uint32_t numBuffers;

    /**
     * If true, indicates the buffers are allocated in zeroCopy memory that is mapped to
     * both the CPU and GPU.  Otherwise, the buffers are only accessible from the GPU.
     * @note the default is true (zeroCopy CPU/GPU access enabled).
     */
    bool zeroCopy;

    /**
     * Control the number of loops for videoSource disk-based inputs (for example,
     * the number of times that a video should loop). Other types of streams will ignore it.
     *
     * The following values are are valid:
     *
     *   -1 = loop forever
     *    0 = don't loop
     *   >0 = set number of loops
     *
     * This option can be set from the command line using `--loop=N`.
     * @note by default, looping is disabled (set to `0`).
     */
    int loop;

    /**
     * Number of milliseconds of video to buffer for incoming RTSP streams (the default is 2000 ms).
     * This option can be set from the command line using `--input-rtsp-latency=N`
     */
    int rtspLatency;

    /**
     * Device interface types.
     */
    enum DeviceType
    {
        DEVICE_DEFAULT = 0,		/**< Unknown interface type. */
        DEVICE_V4L2,			/**< V4L2 webcam (e.g. `/dev/video0`) */
        DEVICE_CSI,			/**< MIPI CSI camera */
        DEVICE_IP,			/**< IP-based network stream (e.g. RTP/RTSP) */
        DEVICE_FILE,			/**< Disk-based stream from a file or directory of files */
        DEVICE_DISPLAY			/**< OpenGL output stream rendered to an attached display */
    };

    /**
     * Indicates the type of device interface used by this stream.
     */
    DeviceType deviceType;

    /**
     * Input/Output stream type.
     */
    enum IoType
    {
        INPUT = 0,			/**< Input stream (e.g. camera, video/image file, ect.) */
        OUTPUT,				/**< Output stream (e.g. display, video/image file, ect.) */
    };

    /**
     * Indicates if this stream is an input or an output.
     */
    IoType ioType;

    /**
     * Settings of the flip method used by MIPI CSI cameras and compressed video inputs.
     */
    enum FlipMethod
    {
        FLIP_NONE = 0,				/**< Identity (no rotation) */
        FLIP_COUNTERCLOCKWISE,		/**< Rotate counter-clockwise 90 degrees */
        FLIP_ROTATE_180,			/**< Rotate 180 degrees */
        FLIP_CLOCKWISE,			/**< Rotate clockwise 90 degrees */
        FLIP_HORIZONTAL,			/**< Flip horizontally */
        FLIP_UPPER_RIGHT_DIAGONAL,	/**< Flip across upper right/lower left diagonal */
        FLIP_VERTICAL,				/**< Flip vertically */
        FLIP_UPPER_LEFT_DIAGONAL,	/**< Flip across upper left/lower right diagonal */
        FLIP_DEFAULT = FLIP_NONE		/**< Default setting (none) */
    };

    /**
     * The flip method controls if and how an input frame is flipped/rotated in pre-processing
     * from a MIPI CSI camera or compressed video input. Other types of streams will ignore this.
     *
     * This option can be set from the command line using `--flip-method=xyz`, where `xyz` is one
     * of the strings below:
     *
     *   - `none`                 (Identity, no rotation)
     *   - `counterclockwise`     (Rotate counter-clockwise 90 degrees)
     *   - `rotate-180`           (Rotate 180 degrees)
     *   - `clockwise`            (Rotate clockwise 90 degrees)
     *   - `horizontal-flip`      (Flip horizontally)
     *   - `vertical-flip`        (Flip vertically)
     *   - `upper-right-diagonal` (Flip across upper right/lower left diagonal)
     *   - `upper-left-diagonal`  (Flip across upper left/lower right diagonal)
     */
    FlipMethod flipMethod;

    /**
     * Video codec types.
     */
    enum Codec
    {
        CODEC_UNKNOWN = 0,		/**< Unknown/unsupported codec */
        CODEC_RAW,			/**< Uncompressed (e.g. RGB) */
        CODEC_H264,			/**< H.264 */
        CODEC_H265,			/**< H.265 */
        CODEC_VP8,			/**< VP8 */
        CODEC_VP9,			/**< VP9 */
        CODEC_MPEG2,			/**< MPEG2 (decode only) */
        CODEC_MPEG4,			/**< MPEG4 (decode only) */
        CODEC_MJPEG			/**< MJPEG */
    };

    /**
     * Indicates the codec used by the stream.
     * This is only really applicable to compressed streams, otherwise it will be `CODEC_RAW`.
     *
     * videoSource input streams will attempt to discover the codec type (i.e. from video file),
     * however RTP streams need this to be explitly set using the `--input-codec=xyz` option
     * (where `xyz` is a string like `h264`, `h265`, `vp8`, `vp9`, `mpeg2`, `mpeg4`, or `mjpeg`).
     *
     * A compressed videoOutput stream will default to H.264 encoding, but can be set using
     * the `--output-codec=xyz` command line option (same values for `xyz` as above).
     */
    Codec codec;

    /**
     * Log the video settings, with an optional prefix label.
     */
    void Print( const char* prefix=NULL ) const;

    /**
     * @internal Parse the video resource URI and options.
     */
    bool Parse( const char* URI, const int argc, char** argv, IoType ioType, const char* extraFlag=NULL);

    /**
     * @internal Parse the video resource URI and options.
     */
    bool Parse( const char* URI, const commandLine& cmdLine, IoType ioType);

    /**
     * @internal Parse the video resource URI and options.
     */
    bool Parse( const int argc, char** argv, IoType ioType, int ioPositionArg=-1 );

    /**
     * @internal Parse the video resource URI and options.
     */
    bool Parse( const commandLine& cmdLine, IoType ioType, int ioPositionArg=-1 );

    /**
     * Convert an IoType enum to a string.
     */
    static const char* IoTypeToStr( IoType type );

    /**
     * Parse an IoType enum from a string.
     */
    static IoType IoTypeFromStr( const char* str );

    /**
     * Convert a DeviceType enum to a string.
     */
    static const char* DeviceTypeToStr( DeviceType type );

    /**
     * Parse a DeviceType enum from a string.
     */
    static DeviceType DeviceTypeFromStr( const char* str );

    /**
     * Convert a WbMode enum to a string.
     */
    static const char* WbModeToStr( WbMode type );

    /**
     * Parse a WbMode enum from a string.
     */
    static WbMode WbModeFromStr( const char* str );

    /**
     * Convert a FlipMethod enum to a string.
     */
    static const char* FlipMethodToStr( FlipMethod flip );

    /**
     * Parse a FlipMethod enum from a string.
     */
    static FlipMethod FlipMethodFromStr( const char* str );

    /**
     * Convert a Codec enum to a string.
     */
    static const char* CodecToStr( Codec codec );

    /**
     * Parse a Codec enum from a string.
     */
    static Codec CodecFromStr( const char* str );
};


/**
 * @ingroup video
 */
#define LOG_VIDEO "[video]  "

#endif

