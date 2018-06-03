# MorseCode 1.0

## General purpose
The general purpose of MorseCode is automatic decoding CW signals, sending CW signal using Morse code and visualizing any sound to manually decoding based on spectrogram. The other puspose is displaying spectrogram of any recorded sound.

## Control sections in main interface
The main interface has following control sections:
* __Control__ - Contains controls to start and stop working, open general settings, display visualization in separate window and display program information. This is only section, which cannot be hidden.
* __Rerecord control__ - Allows to rewind and re-record previous sound using audio buffer.  Works only, if record audio to file is enabled, buffer size is not limited.
* __Rerecord speed__ - Contains slider control to change radio of visualizations speed to real time, works only, if record audio to file is enabled, buffer size is not limited.
* __Morse code__ - Provides encoding and decoding CW signal using Morse code.
* __Spectrogram display__ - Contains parameters of spectrogram display, this parameters not affects in CW decoding.
* __Audio processing__ - Contains parameters of audio, which are used in CW decoding.

## Basic control and displaying spectrogram
To display spectrogram, click the Start button in Control section. Spectrogram will be displayed continuously. You can change following parameters in Spectrogram display section:
* __Gain__ - Gain/amplify/brightness of signal, it should be adjusted to signal strength and signal parts to be shown. Overflown signal are not shown.
* __Resolution__ - Number of Fourier transformation points. The lower values will show signal sharper in time, but smoother in frequency, the higher values will show signal sharper in frequency, but smoother in time.
* __Window__ - Fraction of transform window to be calculated. Value changing affects similarly to Resolution value.
* __Zoom__ - Whole spectrogram height in pixels.
* __Offset__ - Adjust spectrogram position vertically.
* __Step__ - Number of audio samples per one pixel of spectrogram.
* __Base__ - Offset of signal value drawn in spectrogram, can reduce displaying background noise and highlight weak signals.
* __Min/Max__ - Number of adjacent current spectrum values to get minimum (negative value) or maximum (positive value). This setting may highlight or hide weak signals.
* __Lines__ - Number of spectrogram lines to display longer signal history.
Below mentioned parameters, you can change display modes:
* __Normal__ - Spectrogram is drawing from left to right in screen in one line.
* __Half offset__ - Spectrogram is drawing parallel in two lines, which one of this is offset half-length of line. This second line makes easier to watch signals, which are broken on first line ends.
* __Scrolling__ - Whole spectrogram moves horizontally, automated decoding does not work in this mode.
You can display signal volume instead of spectrogram using this field. You can also change displaying volume unit below spectrogram in one of following modes:
* __None__ - Displays spectrogram only.
* __VU only__ - Displays spectrogram with volume unit of filtered and reference signal.
* __Signal only__ - Displays spectrogram with calculated and manually corrected discrete signal which is used to decode CW.
* __VU and signal__ - Displays both VU and discrete signal.
If you want to automatically decode CW, you have to use &quot;Signal&quot; only or &quot;VU and signal&quot; setting. During changing spectrogram display parameters, discrete signal will not be repainted, because this signal is generated sequentially and may be adjusted by user before processing.

## Filtered and reference signal
During displaying spectrogram, you can set frequency bounds to make band pass filter to create filtered signal (main signal used to create discrete signal) and referenced signal (used only in reference mode). The filtered signal should be contain only signal which you wish to decode, but reference signal should be contain only background noise signal near filtered signal.
Filtered signal bounds can be adjusted by clicking and dragging on spectrogram using left mouse button. To cancel filtering, you can click above spectrogram in spectrogram screen (in this case, spectrogram zoom value must be smaller than spectrogram line size). Analogically, you can set reference signal bound using right mouse button.

## Audio processing
Before CW decoding, program must generate discrete signal from filtered signal, eventually using reference signal.
There is two ideas, both are based on attack and release signal volume. The volume above attack is interpreted to change discrete signal to up, and volume below release is interpreted to change signal to down. Volume between attack and release does not change discrete signal state, so if attack volume is greater than release volume, discrete signal generator works similar to Schmidt flip-flop. Attack volume cannot be smaller than release volume. If you not use reference signal, volume is the absolute signal strength. If you use reference signal, volume is the filtered to reference signal strength radio, so it is not susceptible for signal with unstable volume, where both filtered signal and reference signal volumes changes proportionally.
You can set processing parameters in __Audio processing__ section.
The __Reference__ check box determines, if reference signal is used, VU of signal window can be calculated in one of three method selectable in drop-down list. For all methods, the filtered signal sample values are squared.
To generate most clearly discrete signal you can adjust following parameters:
* __VU gain__ - gain of VU value
* __VU size__ - size of VU calculating window
* __Attack thr__ and __Release thr__ - Thresholds to get attack (change signal to up) and release threshold (change signal to down). In no-reference mode, value 1000 means full visible VU value, where VU signal display is the whitest (this can be adjusted using __VU gain__). In reference mode, value 1000 means filtered to reference signal radio equaling 10:1.
* __Attack time__ and __Release time__ - Number of signal samples, during signal VU must be above attack or below release value to change discrete signal state. This setting can eliminate false signal changes caused by very short pulse noise or silence.
* __Correction__ - Allow user to manually correct discrete signal. If checked, during painting spectrogram, previously drew discrete signal will be processed instead of current signal, so processing signal is delayed by time needed to draw spectrogram at the same point on screen.

## Displaying VU signal instead of spectrogram
In section __Spectrogram display__ there is a drop-down list with three draw modes, but the lists consists of six item. Three first items (starting with &quot;S&quot;) displays spectrogram, but other items displays volume unit graph. In both cases, either without reference or with reference signal, in this mode, on half of graph height there is VU value which corresponds with maximum displayable VU value on VU display below spectrogram (if displayed).
In case of processing without reference signal, there is shown on filtered signal with thresholds. The red surface presents volume above attach threshold and the green surface presents volume below release threshold.
In case of processing with reference signal, the red color indicates VU above maximum, the green color indicates volume of filtered signal, and the blue color indicates the reference signal volume.

## Discrete signal displaying and processing
Processing audio signal requires to display discrete signal below spectrogram. This bar consists of two indicators.
The first represents discrete signal state triggers according to filtered signal volume or filtered to reference signal volume ratio. The red color indicates attack (change up) and green indicates release (change down). The black color indicates no changing state. This indicator are not include attack and release time.
The second indicator represents discrete signal state which includes attack and release time and this signal will be processed in decoder. The black and blue elements represents lower state and the white and yellow elements represents upper state. If manual correction is enabled, you can change this signal by mouse clicking and dragging. Left mouse button turns signal to upper state, right mouse button turns signal to lower state.

## General settings
General settings is available by clicking __Set__ button in __Control__ section. You can set following:
* __Input device__ - Audio device used to record signal to visualize or decode.
* __Output device__ - Audio device used to play generated signal.
* __Sample rate__ - Sample rate of audio for recording and generating.
* __Refresh period__ - Period in milliseconds used to process audio and refresh spectrogram.
* __Record buffer size__ - Size in milliseconds of audio device input buffer, it must be longer than number of samples per refresh period.
* __Player buffer size__ - Size in milliseconds of audio device output buffer, it must be longer than number of samples per refresh period.
* __Player chunk size__ - Period in milliseconds generated at once in sound generating before putting to software buffer.
* __Stereo record__ - Determines, which audio channel is recorded.
* __Repaint timeout__ - Maximum time in milliseconds per refresh timer tick used to repaint spectrogram from buffer after change any spectrogram display parameter. It must be lower than refresh period and adjusted to not freeze spectrogram displaying during repaint.
* __Repaint buffer size__ - Size in seconds of audio buffer used to repaint spectrogram and volume unit indicator after spectrogram display parameter change.
* __Rerecord buffer size__ - Buffer length in seconds to rerecord audio. This buffer is used only, when recording audio to file is disabled. Otherwise, the audio file will be used as buffer.
* __Filters enabled__ - Enables filtering signal (generating filtered and reference signal), but it requires higher computer performance. If disabled, the filtered and reference signal will be the same as raw signal.
* __Draw filtered and draw reference__ - Calculates discrete Fourier transform separately to all three signals (raw, filtered and reference) and displays real signals after filtering instead of just coloring.
* __Filter size__ - Size of IIR filter in samples used to generate filtered and reference signal. Higher value provides more accurate filtering, but requires more computer performance.
* __Player enabled__ - Enabled playing output audio signal, which is required to generate any audio from program. From the drop-down list, you can select, which input signal will be redirected for output. If you select other than &quot;none&quot;, you have to select and configure audio devices in such way, where audio generated by output devise is not recorded by input device. Otherwise, spectrogram and displayed audio will be distorted. The value at right is the compensation difference between playback and recording sample rate. Value equaling 0 means no compensation. Positive values means, that playback is faster than recording and program will add one additional sample per entered number in playing audio. Negative value means, that playback is slower than recording and program will omit one sample per absolute of entered number in playing audio.
* __Playback buffer size__ - Set minimum and maximum amount of milliseconds in software playing buffer to avoid under run (will cause playing errors) or overflow (will cause long delay in playing). Program follows current playing buffer filled with recorded audio. If buffer filling is below minimum, the audio chunk will be grabbed without removing of buffer. If Buffer filling is above maximum, the audio will be removed without playing (putting do player device buffer).
* __Simulate record from file__ - Enables reading audio samples from WAV file instead of realtime recorded samples. This feature is intended for testing purpose, and selected WAV file must be 16-bit PCM, mono or stereo, sample rate should be the same as selected sample rate for recording and playing.
* __Record audio to file__ - Enabled recording all displayed audio to WAV file in selected directory.
* __Show spectrogram parameters__, __Show audio processing parameters__, __Show buffer controllers__, __Show buffer speed slider__, __Show Morse code controllers__ - Shows or hides sections in main window.

## Spectrogram settings
Spectrogram settings are available by clicking __Set__ button in __Spectrogram display__ section. It has following settings:
* __Hide mouse cursor__ - Enable hiding mouse cursor on spectrogram window. Usable on computers with touch-sensitive screen.
* __Spectrogram toolbar__ - Position and size of toolbar on spectrogram window.
* __Compute decimation__ - Adjust pixel decimation on spectrum computing for minimum display step, on higher display steps, decimation value will be proportionally lower, so calculating frequency will by approximately constant or lower for higher steps, where calculated decimation will be 1. If you check __Constant__ checkbox, the decimation value will be the same for any display settings. Value &quot;1&quot; means no decimation. Use this setting if computer performance is not enough.
* __Window type__ - Selects audio window used to calculate audio spectrum.
* __Display palette__ - Select one of user defined color palettes to display spectrogram and VU.
* __Display gamma x1000__ - Adjust display gamma to get color brightness proportional to signal value.
* __Display Red__, __Display Green__, __Display Blue__ - Sets, which audio signal will be displayed for each color channel.
* __Display negative__ - Inverts color of spectrogram.
* __Overdrive threshold__ - Number of minimum absolute sample value to indicate input signal overdrive. This will be indicated by draw one selected color instead of spectrogram.
* __Spectrogram strip__ - Size and color of spectrogram strip which points the current audio signal. Not affects in case of scrolling display.
* __Spectrogram half marker__ - Size and color of spectrogram half mark displayed in case of half offset mode.
* __Spectrogram scroll cycle__ - Number of pixels (iterations) to draw between scrolling in scrolling mode. The lover values makes display more smooth, but may require more computer performance.
* __Draw markers__ - Draw frequency markers defined in field below. Every marker is defined by five numbers. The first is the audio frequency, the second is the thickness in pixels and three next numbers defines marker color. The number have to be separated by any non-digital character, further number than the first five will be ignored. Every marker must be defined in separate line.

## Morse code decoding
Morse code decoding from CW keyed signal is based on analysis discrete pulse signal generated and eventually manually corrected. Program analyzes length of every pulse (high state period) and silence between pulses (low state period). The threshold between short pulse and ling signal is connected with signal speed.
If decoder is enabled, all pulse and break timer is buffered, so you can decode the same signal many times. To enable decoder, you have to check __Work__ in __Morse code__ section. You can display output (decoded) text by clicking __Outp__ button. You can do following actions using controls in __Morse code__ section. All characters not contained in dictionary will be displayed as &quot;.&quot; and &quot;-&quot; sequence between &quot;{&quot; and &quot;}&quot;.
* __Set__ - Display settings.
* __Calc__ - Calculate speed based on last signals.
* __Clear__ - Clear buffer.
* __Whole__ - Decode all buffered signals using current calculated parameters.
* __Last__ - Decode last couple of signals. This number of signal is set in setup window.
* __Current__ - Decode signals not decoded already.
* __Real__ - Displays decoded text automatically in real time.

## Generating Morse code signal
You can generate Morse code audio signal using input text window available after clicking __Inp__ button in __Morse code__ section. In this window, you can set the speed in characters per minute. If you set positive value, the value will be constant. If you set zero or negative value, this value will be replaced by calculated decoding speed at text sending moment.
You can send text in three ways:
* __&quot;Send&quot; button__ - text will be transmitted only after clicking __Send__ button.
* __&quot;Enter&quot; key__ - text will be transmitted every time after pressing __Enter__ key on keyboard.
* __Every key__ - Every char will be transmitted directly after pressing.

## Morse code encoding and decoding settings
If you click Set button in Morse code section, you will get access to Morse code encoding/decoding settings:
* __Last signals to calc__ - Last pulses used to detect signal speed.
* __Short/long threshold__ - Factor between shortest and longest signal used to differ short and long signal.
* __Short pause threshold__ - Minimum pause length in short signal lengths x100  to tread pause as between letters.
* __Long pause threshold__ - Minimum pause length in short signal lengths x100  to tread pause as between words.
* __Calculate button__ - Calculate speed now.
* __Auto calculate__ - Automatic speed calculation after every entered number of pulses.
* __Last signal from buffer__ - Number of signals, which will be analyzed in using __Last__ button in __Morse Code__ section.
* __Test mode__ - Generate continuous tone to test generator.
* __Speed standard__ - Standard of speed used in calculating and displaying speed in chars per minute.
* __Generator volume__ - Volume of generated tone.
* __Sound frequency__ - When checked, sets generator tone frequency. When unchecked, tone generator frequency equals to middle frequency of filtered signal bounds.
* __Mute transmit delay__ - Mute recording sound during transmitting and after transmitting last signal. This time is in millisecond. This sound will be displayed on spectrogram and VU meter will not be displayed. While this period, sound will be treated as silence to avoid affect in receiving sound processing. If this field is not checked, recorded sound will be not muted during transmitting.
* __Transmit display latency__ - Time in milliseconds between sending text and displaying this text in __Output text__ window. This time should be adjusted experimentally to include received text latency.
* __Signal fade value__ - Value change speed per 1 second to eliminate clicks. Too high values may cause clicks, but too low values may cause signal smoothing in time.

## Audio rerecording
Program can buffer recorded sound to display or process more than one time or display slower than real time. In this case, audio can be treated as recorded again, recorded faster or slower. To do this, you can use controls in __Rerecord control__ section and __Rerecord speed__ section.
Using buttons in __Rerecord control__ section, you can following actions:
* __|&lt;__ - Jump to begin of buffer (oldest buffered signal).
* __&gt;|__ - Jump to end of buffer (current signal).
* __&lt;&lt;&lt;__ - Move backward 3 minutes.
* __&gt;&gt;&gt;__ - Move forward 3 minutes.
* __&lt;&lt;__ - Move backward 15 seconds.
* __&gt;&gt;__ - Move forward 15 seconds.
* __|&gt;__ - Set processing speed to 100% - real time current or delayed playing.
* __||__ - Set processing speed to 0% - processing paused, but audio is recorded into buffer.

In section __Rerecord speed__ you can see delay time and current processing speed. You can use the slide control to change processing speed. This change affects in spectrogram drawing speed, but this sound is treated as recorded again. If you set speed above 100%, and sound buffer end is reached, sound will be drawn and processed at 100% speed.

## Spectrogram in separate window or fullscreen
MorseCode offers displaying spectrogram in separate window or fullscreen with buttons to change parameters. This feature is intended to use with touch panel or keyboard.
You can activate separate window by clicking __Spec__ in __Control__ section. Spectrogram or volume unit is displayed in the same way as in main window, but spectrogram is not displayed in main window while separate window is shown.
In this window, you can use buttons using mouse or keyboard keys.
Buttons changing values are twice, has __+__ and __-__ and can be controlled by __[Q][A]__, __[W][S]__, __[E][D]__ etc. key pairs:
* __G__ - __[Q][A]__ - Gain.
* __R__ - __[W][S]__ - Resolution.
* __W__ - __[E][D]__ - Window.
* __Z__ - __[R][F]__ - Zoom.
* __O__ - __[T][G]__ - Offset.
* __S__ - __[Y][H]__ - Step.
* __B__ - __[U][J]__ - Base.
* __M__ - __[I][K]__ - Min/Max.
* __L__ - __[O][L]__ - Lines.

The other three buttons can be controlled by __[Z]__, __[X]__, __[C]__ keys:
* __D__ - __[Z]__ - Toggle display modes around 6-item cycle.
* __P__ - __[X]__ - Pause and resume displaying (requires rerecord buffer).
* __F__ - __[C]__ - Toggle fullscreen.

The last button is __X__, which closes spectrogram window. This button can not be activated by keyboard to avoid accidental window closing.

## Morse code symbol dictionary
At the application directory, there is Symbols.txt file, which contains symbol definition. This file is loaded while MorseCode starts. On line in this file defines one symbol.
Every line has following structure:
1. Morse code of symbol defined using &quot;.&quot; and &quot;-&quot; characters, which means DIT and DAH.
2. Tab character.
3. All symbols separated by &quot;|&quot;, which certain code can mean. While decoding, the first symbol will be displayed, while encoding, all symbols can be used. One symbol may consist of several characters.

Characters &quot;|&quot;, &quot;{&quot; and &quot;}&quot; can not be defined as symbols.

## Display palettes
You can define custom display palettes, which can be used to display spectrogram. To define palette, you have to place bitmap file (BMP or PNG format) which contains this palette drew vertically do application directory. One bitmap file can contain several palettes.
After placing bitmap file or modifying existing file, you have to add entry in Palette.txt. Every entry defines one palette and consists of following five values separated by &quot;|&quot;:
1. Bitmap file name.
2. Number of column of pixels.
3. Number of row which defines lowest value.
4. Number of row which defines highest value.
5. Name displayed in spectrogram settings.

## Compiling and deploying for Windows
At this description, there will be used following wilcards:
* __%MinGW%__ - Directory, where MinGW is installed (for example &quot;C:\\Qt\\Qt5.6\\5.6\\mingw49_32\\&quot;).
* __%Binary%__ - Directory, where binary is placed after building (contains &quot;MorseCode.exe&quot;).

To compile MorseCode for Windows, you have to do following:
1. Install Qt Creator with Qt library and MinGW compiler.
2. Open MorseCode.pro in Qt Creator, click __Configure Project__ in project configuration screen if appears.
3. Build project as release.
4. Run following command: `%MinGW%\\bin\\windeployqt.exe --release %Binary%`.
5. Copy following files from %MinGW%\\bin\\ to %Binary%: libgcc_s_dw2-1.dll, libstdc*6.dll, libwinpthread-1.dll.
6. Remove all *.cpp and *.o files.
7. Place downloaded initial configuration files: Symbols.txt, Palette.txt, Thermal.png, RGB.png.

## Compiling and deploying for Linux
At this description, there will be used following wilcards:
* __%Linuxdeployqt%__ - Directory, where Linuxdeployqt tool is placed.
* __%Binary%__ - Directory, where binary is placed after building (contains &quot;MorseCode&quot; executable file).

To compile MorseCode for Linux equipped with apt-get tool, you have to do following:
1. Upgrade installed packet using following: `sudo apt-get update` and `sudo apt-get upgrade`.
2. Install Qt library and Qt Creator using: `sudo apt-get install build-essential qtcreator qt5-default`.
3. Install multimedia extension for Qt using: `sudo apt-get install libqt5multimedia5 libqt5multimedia5-plugins libqt5multimediawidgets5`.
4. Download &quot;linuxdeployqt-continuous-x86_64.AppImage&quot; from https://github.com/probonopd/linuxdeployqt/releases and place it into %Linuxdeployqt%.
5. Open MorseCode.pro in Qt Creator, click __Configure Project__ in project configuration screen if appears.
6. Build project as release.
7. Run following command to build stanlone application: `'%Linuxdeployqt%\\linuxdeployqt-continuous-x86_64.AppImage' '%Binary%\\MorseCode' -appimage`.
8. Remove all *.h, *.cpp, *.o, .DirIcon, AppRun, default.desktop, default.png and Makefile files.
9. Place downloaded initial configuration files: Symbols.txt, Palette.txt, Thermal.png, RGB.png.
