#include "appcore.h"

AppCore::AppCore()
{
    MorseBufTX = NEWARR(int, int[1]);
    MorseBufTX[0] = 0;
    MorseBuf = NEW(QString, QString());
    MorseEncoderCore_.TextBuf = MorseBuf;
    MorseDecoderCore_.TextBuf = MorseBuf;
    MorseEncoderCore_.TextBufTX = MorseBufTX;
    MorseDecoderCore_.TextBufTX = MorseBufTX;

    XFreqL = 0;
    XFreqH = 0.5;
    XFreqLRef = 0;
    XFreqHRef = 0.5;

    MouseMode = 0;
    MousePressed = false;
    CorrectOffset = 0;

    // Sound buffer from file
    FileAudioData = NEWARR(short, short[1]);
    FileAudioLength = 1;
    FileAudioPointer = 0;

    WithRef = false;

    // Recorded sound buffer
    AudioSrc.Init(100000);

    // Sound buffers to visualize and process
    AudioRaw.Init(100000);
    AudioFil.Init(100000);
    AudioRef.Init(100000);
    AudioPlaybackBuf.Init(100000);

    // Sound volume buffer
    AudioFilVU.Init(10000);
    AudioRefVU.Init(10000);
    AudioCalcVU.Init(10000);

    for (int I = 0; I < SpectrumArraySize; I++)
    {
        SpectrumBufRaw_R[I] = 0;
        SpectrumBufRaw_G[I] = 0;
        SpectrumBufRaw_B[I] = 0;
        SpectrumBufFil_R[I] = 0;
        SpectrumBufFil_G[I] = 0;
        SpectrumBufFil_B[I] = 0;
        SpectrumBufRef_R[I] = 0;
        SpectrumBufRef_G[I] = 0;
        SpectrumBufRef_B[I] = 0;
    }
    SpectrumVUFil_R = 0;
    SpectrumVUFil_G = 0;
    SpectrumVUFil_B = 0;
    SpectrumVURef_R = 0;
    SpectrumVURef_G = 0;
    SpectrumVURef_B = 0;
    SpectrumVUFilX = 0;
    SpectrumVURefX = 0;
    SpectrumVUCalc = 0;
    WindowPointer = 0;
    WindowPointer1 = 0;
    WindowPointer2 = 0;
    VUCalcAttackState = false;

    for (int I = 0; I < FilterWindowWorkSize; I++)
    {
        FilterWindowWork[I] = 0;
        FilterWindowWorkFil[I] = 0;
        FilterWindowWorkRef[I] = 0;
    }
}

AppCore::~AppCore()
{
    if (RepaintBufRaw != NULL)
    {
        DEL(RingBuffer<short>, RepaintBufRaw);
        DEL(RingBuffer<short>, RepaintBufFil);
        DEL(RingBuffer<short>, RepaintBufRef);
        DEL(RingBuffer<short>, RepaintFilVU);
        DEL(RingBuffer<short>, RepaintRefVU);
    }
    DELARR(int, MorseBufTX);
    DELARR(short, FileAudioData);
    DEL(QString, MorseBuf);
}

///
/// \brief AppCore::SetSpectrogramMarkers - Calculating spectrum markers
///
void AppCore::SetSpectrogramMarkers()
{
    if (!Settings_->SpectrogramMarkersUpdate)
    {
        return;
    }
    Settings_->SpectrogramMarkersUpdate = false;

    SpectrumMarkersPosition.clear();
    SpectrumMarkersThickness.clear();
    SpectrumMarkersRed.clear();
    SpectrumMarkersGreen.clear();
    SpectrumMarkersBlue.clear();
    SpectrumMarkers = Settings_->SpectrogramMarkersEnable;

    if ((!SpectrumMarkers) || (Settings_->SampleRate <= 0))
    {
        return;
    }

    // Splitting text to lines
    vector<string> TextLines;
    string Buf = "";
    Settings_->SplitTextToLines(Settings_->SpectrogramMarkers, TextLines, true);

    // Getting numbers from line
    for (uint I = 0; I < TextLines.size(); I++)
    {
        Buf = TextLines[I];
        vector<int> Temp;
        int BufN = 0;
        bool WasFirst = false;
        for (uint II = 0; II < Buf.size(); II++)
        {
            char C = Buf[II];
            if ((C >= '0') && (C <= '9'))
            {
                BufN *= 10;
                BufN += (C - 48);
                WasFirst = true;
            }
            else
            {
                if (WasFirst)
                {
                    Temp.push_back(BufN);
                    BufN = 0;
                    WasFirst = false;
                }
            }
        }

        // If at least five number exists, then marker must be added
        if (Temp.size() >= 5)
        {
            if ((Temp[0] >= 0) && (Temp[1] > 0))
            {
                if ((Temp[2] >= 0) && (Temp[3] >= 0) && (Temp[4] >= 0))
                {
                    if ((Temp[2] <= 255) && (Temp[3] <= 255) && (Temp[4] <= 255))
                    {
                        int F = (Temp[0] * 10240) / Settings_->SampleRate;
                        int T = Temp[1];
                        int M = F % 10;
                        F = F / 10;
                        if (M >= 5)
                        {
                            if ((T % 2) == 0)
                            {
                                F++;
                                F++;
                                F -= T >> 1;
                            }
                            else
                            {
                                F++;
                                F -= (T - 1) >> 1;
                            }
                        }
                        else
                        {
                            if ((T % 2) == 0)
                            {
                                F -= T >> 1;
                            }
                            else
                            {
                                F -= (T - 1) >> 1;
                            }
                        }

                        if ((F < 0) && ((F + T) > 0))
                        {
                            T = T + F;
                            F = 0;
                        }

                        if ((F >= 0) && (T > 0))
                        {
                            SpectrumMarkersPosition.push_back(F);
                            SpectrumMarkersThickness.push_back(T);
                            SpectrumMarkersRed.push_back(Temp[2]);
                            SpectrumMarkersGreen.push_back(Temp[3]);
                            SpectrumMarkersBlue.push_back(Temp[4]);
                        }
                    }
                }
            }
        }
    }
}

///
/// \brief AppCore::SpectrogramGet - Drawing spectrum and other sound information
/// \param BmpRAW
/// \param DispWidth
/// \param DispHeight
///
void AppCore::SpectrogramGet(uchar * BmpRAW, int DispWidth, int DispHeight, char DrawCurrent, int DrawOffset)
{
    int SpectrogramDisplayCurrentLine = SpectrogramDisplayCurrentLine__;
    int SpectrogramPointer = SpectrogramPointer__;
    if (DrawCurrent != 1)
    {
        if (DrawOffset >= (SpectrogramDisplayLines * DispWidth))
        {
            return;
        }
        SpectrogramPointer = SpectrogramPointer - DrawOffset;
        while (SpectrogramPointer < 0)
        {
            SpectrogramPointer += DispWidth;
            SpectrogramDisplayCurrentLine--;
            if (SpectrogramDisplayCurrentLine < 0)
            {
                SpectrogramDisplayCurrentLine += SpectrogramDisplayLines;
            }
        }
    }

    if (SpectrogramDrawVU == 3)
    {
        SpectrogramVolumeBarSize = VUHeight << 2;
    }
    else
    {
        if (SpectrogramDrawVU == 0)
        {
            SpectrogramVolumeBarSize = 0;
        }
        else
        {
            SpectrogramVolumeBarSize = VUHeight << 1;
        }
    }

    SetSpectrogramMarkers();

    SpectrogramDrawLineWidth = DispHeight;
    if (SpectrogramDrawMode == 1)
    {
        SpectrogramDrawLineWidth = (DispHeight / (SpectrogramDisplayLines << 1));
    }
    else
    {
        SpectrogramDrawLineWidth = (DispHeight / SpectrogramDisplayLines);
    }

    SpectrogramDrawVUX = SpectrogramDrawVU;
    if (SpectrogramVolumeBarSize > 0)
    {
        if (SpectrogramVolumeBarSize > SpectrogramDrawLineWidth)
        {
            SpectrogramVolumeBarSize = 0;
            SpectrogramDrawVUX = 0;
        }
    }

    // Recalculating marker positions against zoom
    SpectrumMarkersPositionX.clear();
    SpectrumMarkersThicknessX.clear();
    for (uint I = 0; I < SpectrumMarkersPosition.size(); I++)
    {
        if (SpectrogramZoom >= 0)
        {
            int XXX = ((SpectrumMarkersPosition[I] << SpectrogramZoom) + (SpectrumMarkersThickness[I] << SpectrogramZoom));
            XXX = XXX - (SpectrogramOffset << SpectrogramZoom);
            XXX = SpectrogramDrawLineWidth - XXX;
            int Thickness = SpectrumMarkersThickness[I] << SpectrogramZoom;
            if (XXX >= 0)
            {
                SpectrumMarkersPositionX.push_back(XXX);
                SpectrumMarkersThicknessX.push_back(Thickness);
            }
            else
            {
                int XXXX = Thickness;
                if ((XXX + XXXX) > 0)
                {
                    SpectrumMarkersPositionX.push_back(0);
                    SpectrumMarkersThicknessX.push_back(XXXX + XXX);
                }
            }
        }
        else
        {
            int SpectrogramZoomX = 0 - SpectrogramZoom;
            int XXX = ((SpectrumMarkersPosition[I] >> SpectrogramZoomX) + (SpectrumMarkersThickness[I] >> SpectrogramZoomX));
            XXX = XXX - (SpectrogramOffset >> SpectrogramZoomX);
            XXX = SpectrogramDrawLineWidth - XXX;
            int Thickness = SpectrumMarkersThickness[I] >> SpectrogramZoomX;
            if (Thickness < 1)
            {
                Thickness = 1;
            }
            if (XXX >= 0)
            {
                SpectrumMarkersPositionX.push_back(XXX);
                SpectrumMarkersThicknessX.push_back(Thickness);
            }
            else
            {
                int XXXX = Thickness;
                if ((XXX + XXXX) > 0)
                {
                    SpectrumMarkersPositionX.push_back(0);
                    SpectrumMarkersThicknessX.push_back(XXXX + XXX);
                }
            }
        }
    }

    if (SpectrogramDisplayCurrentLine >= SpectrogramDisplayLines)
    {
        SpectrogramDisplayCurrentLine = 0;
    }

    if ((DispWidth < 1) || (DispHeight < 1))
    {
        return;
    }

    int DispHeightAll = DispHeight;
    DispHeight = DispHeight / SpectrogramDisplayLines;

    if (SpectrogramDrawMode == 2)
    {
        SpectrogramDisplayCurrentLine = SpectrogramDisplayLines - 1;
        if (DrawCurrent == 0)
        {
            while (DrawOffset > DispWidth)
            {
                DrawOffset -= DispWidth;
                SpectrogramDisplayCurrentLine--;
            }
            if (SpectrogramDisplayCurrentLine < 0)
            {
                return;
            }
        }
    }

    // In half-offset method, the height must be a multiply of 2
    if (SpectrogramDrawMode == 1)
    {
        DispHeight = DispHeight >> 1;
    }


    int CurrentLineOffset = (SpectrogramDisplayCurrentLine * SpectrogramFullMaxW * (DispHeight << ((SpectrogramDrawMode == 1) ? 3 : 2)));

    int DrawMargin = Settings_->SpectrogramStrip;
    int DrawMargin2 = Settings_->SpectrogramStrip;
    uchar StripR = Settings_->SpectrogramStripColorR;
    uchar StripG = Settings_->SpectrogramStripColorG;
    uchar StripB = Settings_->SpectrogramStripColorB;
    bool DrawNegative = Settings_->SpectrogramNegative;
    uchar R, G, B, CR, CG, CB;
    uchar DrawC_R[4];
    uchar DrawC_G[4];
    uchar DrawC_B[4];
    int X, Y, I, II;
    int SpectrogramPointer2;
    DrawC_R[3] = 0;
    DrawC_G[3] = 0;
    DrawC_B[3] = 0;

    // Assigning signal kinds to color channels
    CR = Settings_->SpectrumDisplayR;
    CG = Settings_->SpectrumDisplayG;
    CB = Settings_->SpectrumDisplayB;

    // Calculating place to draw additional line of spectrum
    int CurrentLineOffset2;
    SpectrogramPointer2 = SpectrogramPointer - (DispWidth >> 1);
    if (SpectrogramPointer2 < 0)
    {
        SpectrogramPointer2 = SpectrogramPointer2 + (SpectrogramFullMaxW * DispHeight);
        SpectrogramPointer2 = SpectrogramPointer2 + DispWidth;
        if (SpectrogramDisplayCurrentLine == (0))
        {
            CurrentLineOffset2 = ((SpectrogramDisplayLines - 1) * SpectrogramFullMaxW * (DispHeight << 3));
        }
        else
        {
            CurrentLineOffset2 = ((SpectrogramDisplayCurrentLine - 1) * SpectrogramFullMaxW * (DispHeight << 3));
        }
    }
    else
    {
        CurrentLineOffset2 = (SpectrogramDisplayCurrentLine * SpectrogramFullMaxW * (DispHeight << 3));
        SpectrogramPointer2 = SpectrogramPointer2 + (SpectrogramFullMaxW * DispHeight);
    }

    // Calculating spectrogram strip size
    if ((SpectrogramPointer + DrawMargin) > DispWidth)
    {
        DrawMargin = DispWidth - SpectrogramPointer;
    }
    if ((SpectrogramPointer2 + DrawMargin2) > DispWidth)
    {
        DrawMargin2 = DispWidth - SpectrogramPointer2;
    }

    int PO = 0;
    int PO2 = 0;
    if (SpectrogramDrawMode == 2)
    {
        if (DrawCurrent == 1)
        {
            // Moving picture left by one pixel
            if (SpectrogramPointerScroll <= 0)
            {
                SpectrogramPointerScroll = Settings_->SpectrogramScrollCycle;
                PO = 0;
                int CopyOffset = (SpectrogramFullMaxW * DispHeight) << 2;
                int Ymax = (DispHeight * SpectrogramDisplayCurrentLine);
                for (Y = 0; Y < Ymax; Y++)
                {
                    memmove(BmpRAW + PO + (DispWidth << 2), BmpRAW + PO + CopyOffset, Settings_->SpectrogramScrollCycle << 2);
                    PO += SpectrogramFullMaxW4;
                }
                PO = 0;
                for (Y = 0; Y < DispHeightAll; Y++)
                {
                    memmove(BmpRAW + PO, BmpRAW + PO + (Settings_->SpectrogramScrollCycle << 2), (DispWidth + Settings_->SpectrogramScrollCycle) << 2);
                    PO += SpectrogramFullMaxW4;
                }
            }
            SpectrogramPointerScroll--;
            PO = (DispWidth - 1 - SpectrogramPointerScroll + Settings_->SpectrogramScrollCycle) << 2;
        }
        else
        {
            PO = (DispWidth - DrawOffset) << 2;
        }

        SpectrogramPointer = 0;
    }
    else
    {
        if ((DrawCurrent == 1) || (DrawCurrent == 2))
        {
            // Drawing spectrogram strip
            PO = (SpectrogramPointer + 1) << 2;
            PO2 = (SpectrogramPointer2 + 1) << 2;
            I = DispHeight;
            for (Y = 0; Y < I; Y++)
            {
                for (X = 0; X < DrawMargin; X++)
                {
                    BmpRAW[PO + CurrentLineOffset + 0] = StripB;
                    BmpRAW[PO + CurrentLineOffset + 1] = StripG;
                    BmpRAW[PO + CurrentLineOffset + 2] = StripR;
                    PO += 4;
                    if (SpectrogramDrawMode == 1)
                    {
                        BmpRAW[PO2 + CurrentLineOffset2 + 0] = StripB;
                        BmpRAW[PO2 + CurrentLineOffset2 + 1] = StripG;
                        BmpRAW[PO2 + CurrentLineOffset2 + 2] = StripR;
                        PO2 += 4;
                    }
                }
                PO += (SpectrogramFullMaxW - DrawMargin) << 2;
                PO2 += (SpectrogramFullMaxW - DrawMargin) << 2;
            }

            if (DrawCurrent == 2)
            {
                // Drawing half marker
                if ((SpectrogramDrawMode == 1) && (Settings_->HalfMarkSize > 0))
                {
                    int W = Settings_->HalfMarkSize;
                    int PO__ = (DispWidth >> 1);
                    PO__ = PO__ - (W >> 1);
                    if (PO__ >= 0)
                    {
                        W = W << 2;
                        PO__ = PO__ << 2;
                        uchar R = Settings_->HalfMarkColorR;
                        uchar G = Settings_->HalfMarkColorG;
                        uchar B = Settings_->HalfMarkColorB;
                        for (Y = (((DispHeight * SpectrogramDisplayLines) << 1) - 1); Y >= 0; Y--)
                        {
                            for (X = 0; X < W; X+=4)
                            {
                                BmpRAW[PO__ + X + 0] = B;
                                BmpRAW[PO__ + X + 1] = G;
                                BmpRAW[PO__ + X + 2] = R;
                            }
                            PO__ += SpectrogramFullMaxW4;
                        }
                    }
                }


                return;
            }
        }
        PO = SpectrogramPointer << 2;
        PO2 = SpectrogramPointer2 << 2;
    }









    int DrawF1 = SpectrumResolutionFactorX;
    int DrawF2 = SpectrogramResolution + SpectrogramZoom;
    if (DrawF1 < DrawF2)
    {
        DrawF2 = DrawF2 - DrawF1;
        DrawF1 = 0;
    }
    else
    {
        if (DrawF2 < DrawF1)
        {
            DrawF1 = DrawF1 - DrawF2;
            DrawF2 = 0;
        }
        else
        {
            if (DrawF1 == DrawF2)
            {
                DrawF1 = 0;
                DrawF2 = 0;
            }
        }
    }
    int DrawF3 = (DrawF2 - DrawF1) - (SpectrogramZoom);

    // DrawF1 - Pixels of graph to pixels of surface (bit move)
    // DrawF2 - Pixels of surface to pixels of graph (bit move)
    //cout << DrawF1 << " " << DrawF2 << endl;
    //cout << SpectrogramResolution << " " << SpectrogramZoom << endl;

    X = 0;
    int SpecI = 0;

    int SpecIOffset = 0;
    if (SpectrogramResolution >= 3)
    {
        SpecIOffset = (SpectrogramOffset >> (SpectrogramResolution - 3));
    }
    else
    {
        SpecIOffset = (SpectrogramOffset << (3 - SpectrogramResolution));
    }

    if (SpectrumBufOverload)
    {
        for (Y = (SpectrogramDrawLineWidth - 1); Y >= 0; Y--)
        {
            SpectrogramTempB[X] = Settings_->OverloadColorB;
            SpectrogramTempG[X] = Settings_->OverloadColorG;
            SpectrogramTempR[X] = Settings_->OverloadColorR;
            X++;
        }
    }
    else
    {
        if (SpectrogramDrawVolume)
        {
            int SpectrogramZoomXX;
            int SpectrogramZoomXXX;
            int SpectrogramOffsetX = SpectrogramOffset;
            int SpectrumVUFilX_;
            int SpectrumVURefX_;

            if (SpectrogramZoom >= 0)
            {
                SpectrogramZoomXX = 512 << SpectrogramZoom;
                SpectrogramZoomXXX = 256 << SpectrogramZoom;
                if (SpectrogramZoom == 0)
                {
                    SpectrogramOffsetX = SpectrogramOffset >> 1;
                }
                else
                {
                    if (SpectrogramZoom >= 2)
                    {
                        SpectrogramOffsetX = SpectrogramOffset << (SpectrogramZoom - 1);
                    }
                }
                SpectrumVUFilX_ = SpectrumVUFilX << SpectrogramZoom;
                SpectrumVURefX_ = SpectrumVURefX << SpectrogramZoom;
            }
            else
            {
                int SpectrogramZoom0 = 0 - SpectrogramZoom;
                SpectrogramZoomXX = 512 >> SpectrogramZoom0;
                SpectrogramZoomXXX = 256 >> SpectrogramZoom0;
                SpectrogramOffsetX = SpectrogramOffset >> (SpectrogramZoom0 + 1);
                SpectrumVUFilX_ = SpectrumVUFilX >> SpectrogramZoom0;
                SpectrumVURefX_ = SpectrumVURefX >> SpectrogramZoom0;
            }
            double SpectrogramZoomXXX_ = SpectrogramZoomXXX;
            int VUCalcAttackThreshold_ = ((VUCalcAttackThreshold / 2.5) * SpectrogramZoomXXX_);
            int VUCalcDecayThreshold_ = ((VUCalcDecayThreshold / 2.5) * SpectrogramZoomXXX_);


            int Y_;
            for (Y = ((SpectrogramDrawLineWidth) - 1); Y >= 0; Y--)
            {
                Y_ = Y + SpectrogramOffsetX;
                if (Y_ <= SpectrogramZoomXX)
                {
                    R = 0;
                    G = 0;
                    B = 0;
                    if (WithRef)
                    {
                        if (Y_ >= SpectrogramZoomXXX)
                        {
                            R = 128;
                        }
                        if (Y_ <= SpectrumVUFilX_)
                        {
                            G = 255;
                        }
                        if (Y_ <= SpectrumVURefX_)
                        {
                            B = 255;
                        }
                    }
                    else
                    {
                        if (Y_ <= SpectrumVUFilX_)
                        {
                            if (Y_ < SpectrogramZoomXXX)
                            {
                                R = 192;
                                G = 192;
                            }
                            else
                            {
                                R = 128;
                                G = 128;
                            }
                            B = 255;
                        }
                        if (Y_ >= VUCalcAttackThreshold_)
                        {
                            R = 255;
                        }
                        if (Y_ <= VUCalcDecayThreshold_)
                        {
                            G = 255;
                        }
                    }
                    SpectrogramTempB[X] = B;
                    SpectrogramTempG[X] = G;
                    SpectrogramTempR[X] = R;
                }
                else
                {
                    SpectrogramTempB[X] = 0;
                    SpectrogramTempG[X] = 0;
                    SpectrogramTempR[X] = 0;
                }
                X++;
            }
        }
        else
        {
            for (Y = ((SpectrogramDrawLineWidth >> (DrawF2)) - 1); Y >= 0; Y--)
            {
                // Downscaling
                if (DrawF1 == 0)
                {
                    SpecI = Y + SpecIOffset;
                }
                else
                {
                    SpecI = (Y << DrawF1) + SpecIOffset;

                    int T_R = 0;
                    int T_G = 0;
                    int T_B = 0;
                    for (II = ((1 << DrawF1) - 1); II >= 0; II--)
                    {
                        T_R += ((int)SpectrumBufRaw_R[SpecI + II]);
                        T_G += ((int)SpectrumBufRaw_G[SpecI + II]);
                        T_B += ((int)SpectrumBufRaw_B[SpecI + II]);
                    }
                    SpectrumBufRaw_R[SpecI] = T_R >> DrawF1;
                    SpectrumBufRaw_G[SpecI] = T_G >> DrawF1;
                    SpectrumBufRaw_B[SpecI] = T_B >> DrawF1;
                    if (Settings_->DrawFil)
                    {
                        T_R = 0;
                        T_G = 0;
                        T_B = 0;
                        for (II = ((1 << DrawF1) - 1); II >= 0; II--)
                        {
                            T_R += ((int)SpectrumBufFil_R[SpecI + II]);
                            T_G += ((int)SpectrumBufFil_G[SpecI + II]);
                            T_B += ((int)SpectrumBufFil_B[SpecI + II]);
                        }
                        SpectrumBufFil_R[SpecI] = T_R >> DrawF1;
                        SpectrumBufFil_G[SpecI] = T_G >> DrawF1;
                        SpectrumBufFil_B[SpecI] = T_B >> DrawF1;
                    }
                    if (Settings_->DrawRef)
                    {
                        T_R = 0;
                        T_G = 0;
                        T_B = 0;
                        for (II = ((1 << DrawF1) - 1); II >= 0; II--)
                        {
                            T_R += ((int)SpectrumBufRef_R[SpecI + II]);
                            T_G += ((int)SpectrumBufRef_G[SpecI + II]);
                            T_B += ((int)SpectrumBufRef_B[SpecI + II]);
                        }
                        SpectrumBufRef_R[SpecI] = T_R >> DrawF1;
                        SpectrumBufRef_G[SpecI] = T_G >> DrawF1;
                        SpectrumBufRef_B[SpecI] = T_B >> DrawF1;
                    }
                }

                if (SpecI >= SpectrumArraySize)
                {
                    R = 0;
                    G = 0;
                    B = 0;
                }
                else
                {
                    DrawC_R[0] = SpectrumBufRaw_R[SpecI];
                    DrawC_G[0] = SpectrumBufRaw_G[SpecI];
                    DrawC_B[0] = SpectrumBufRaw_B[SpecI];
                    if (Settings_->DrawFil)
                    {
                        DrawC_R[1] = SpectrumBufFil_R[SpecI];
                        DrawC_G[1] = SpectrumBufFil_G[SpecI];
                        DrawC_B[1] = SpectrumBufFil_B[SpecI];
                    }
                    else
                    {
                        DrawC_R[1] = 0;
                        DrawC_G[1] = 0;
                        DrawC_B[1] = 0;
                        if (DrawF3 < 0)
                        {
                            if ((SpecI >= (XFreqL__ << (0 - DrawF3))) && (SpecI <= (XFreqH__ << (0 - DrawF3))))
                            {
                                DrawC_R[1] = DrawC_R[0];
                                DrawC_G[1] = DrawC_G[0];
                                DrawC_B[1] = DrawC_B[0];
                            }
                        }
                        else
                        {
                            if ((SpecI >= (XFreqL__ >> DrawF3)) && (SpecI <= (XFreqH__ >> DrawF3)))
                            {
                                DrawC_R[1] = DrawC_R[0];
                                DrawC_G[1] = DrawC_G[0];
                                DrawC_B[1] = DrawC_B[0];
                            }
                        }
                    }
                    if (Settings_->DrawRef)
                    {
                        DrawC_R[2] = SpectrumBufRef_R[SpecI];
                        DrawC_G[2] = SpectrumBufRef_G[SpecI];
                        DrawC_B[2] = SpectrumBufRef_B[SpecI];
                    }
                    else
                    {
                        DrawC_R[2] = 0;
                        DrawC_G[2] = 0;
                        DrawC_B[2] = 0;
                        if (DrawF3 < 0)
                        {
                            if ((SpecI >= (XFreqLRef__ << (0 - DrawF3))) && (SpecI <= (XFreqHRef__ << (0 - DrawF3))))
                            {
                                DrawC_R[2] = DrawC_R[0];
                                DrawC_G[2] = DrawC_G[0];
                                DrawC_B[2] = DrawC_B[0];
                            }
                        }
                        else
                        {
                            if ((SpecI >= (XFreqLRef__ >> DrawF3)) && (SpecI <= (XFreqHRef__ >> DrawF3)))
                            {
                                DrawC_R[2] = DrawC_R[0];
                                DrawC_G[2] = DrawC_G[0];
                                DrawC_B[2] = DrawC_B[0];
                            }
                        }
                    }


                    R = DrawC_R[CR];
                    G = DrawC_G[CG];
                    B = DrawC_B[CB];
                }

                // Upscaling
                for (I = (1 << (DrawF2)); I > 0; I--)
                {
                    if (DrawNegative)
                    {
                        SpectrogramTempB[X] = 255 - B;
                        SpectrogramTempG[X] = 255 - G;
                        SpectrogramTempR[X] = 255 - R;
                    }
                    else
                    {
                        SpectrogramTempB[X] = B;
                        SpectrogramTempG[X] = G;
                        SpectrogramTempR[X] = R;
                    }
                    X++;
                }
            }
        }
    }

    // Putting markers
    if (SpectrumMarkers && (!SpectrogramDrawVolume))
    {
        for (uint UI = 0; UI < SpectrumMarkersPositionX.size(); UI++)
        {
            for (uint II = 0; II < SpectrumMarkersThicknessX[UI]; II++)
            {
                SpectrogramTempR[SpectrumMarkersPositionX[UI] + II] = SpectrumMarkersRed[UI];
                SpectrogramTempG[SpectrumMarkersPositionX[UI] + II] = SpectrumMarkersGreen[UI];
                SpectrogramTempB[SpectrumMarkersPositionX[UI] + II] = SpectrumMarkersBlue[UI];
            }
        }
    }

    // Clearing spectrogram after resize
    int POX = 0;
    bool ForceClear = false;
    if ((DispHeightLast != DispHeightAll) || (DispWidthLast != DispWidth))
    {
        for (Y = 0; Y < DispHeightAll; Y++)
        {
            for (X = 0; X < (DispWidth << 2); X += 4)
            {
                BmpRAW[POX + X + 0] = 0;
                BmpRAW[POX + X + 1] = 0;
                BmpRAW[POX + X + 2] = 0;
            }
            POX += SpectrogramFullMaxW4;
        }
        DispHeightLast = DispHeightAll;
        DispWidthLast = DispWidth;
        ForceClear = true;
    }

    // Drawing spectrogram
    uchar BlankColor = DrawNegative ? 255 : 0;
    int T = SpectrogramVolumeBarSize;
    int DispHeightX = DispHeight - SpectrogramVolumeBarSize;
    for (I = 0; I < DispHeightX; I++)
    {
        if ((I + T) < SpectrumArraySize)
        {
            BmpRAW[PO + CurrentLineOffset + 0] = SpectrogramTempB[I + T];
            BmpRAW[PO + CurrentLineOffset + 1] = SpectrogramTempG[I + T];
            BmpRAW[PO + CurrentLineOffset + 2] = SpectrogramTempR[I + T];
        }
        else
        {
            BmpRAW[PO + CurrentLineOffset + 0] = BlankColor;
            BmpRAW[PO + CurrentLineOffset + 1] = BlankColor;
            BmpRAW[PO + CurrentLineOffset + 2] = BlankColor;
        }

        if (SpectrogramDrawMode == 1)
        {
            BmpRAW[PO2 + CurrentLineOffset2 + 0] = BmpRAW[PO + CurrentLineOffset + 0];
            BmpRAW[PO2 + CurrentLineOffset2 + 1] = BmpRAW[PO + CurrentLineOffset + 1];
            BmpRAW[PO2 + CurrentLineOffset2 + 2] = BmpRAW[PO + CurrentLineOffset + 2];

            PO2 += SpectrogramFullMaxW4;
        }

        PO += SpectrogramFullMaxW4;
    }

    // Drawing half marker
    if ((DrawCurrent == 1) && (SpectrogramDrawMode == 1) && (Settings_->HalfMarkSize > 0))
    {
        int W = Settings_->HalfMarkSize;
        int PO__ = (DispWidth >> 1);
        PO__ = PO__ - (W >> 1);
        if (PO__ >= 0)
        {
            W = W << 2;
            PO__ = PO__ << 2;
            uchar R = Settings_->HalfMarkColorR;
            uchar G = Settings_->HalfMarkColorG;
            uchar B = Settings_->HalfMarkColorB;
            for (Y = (((DispHeight * SpectrogramDisplayLines) << 1) - 1); Y >= 0; Y--)
            {
                for (X = 0; X < W; X+=4)
                {
                    BmpRAW[PO__ + X + 0] = B;
                    BmpRAW[PO__ + X + 1] = G;
                    BmpRAW[PO__ + X + 2] = R;
                }
                PO__ += SpectrogramFullMaxW4;
            }
        }
    }

    if (SpectrogramVolumeBarSize > 0)
    {
        if ((SpectrogramDrawVU == 1) || (SpectrogramDrawVU == 3))
        {
            // Drawing volume levels
            for (I = (VUHeight - 1); I >= 0; I--)
            {
                BmpRAW[PO + CurrentLineOffset + 0] = SpectrumVURef_B;
                BmpRAW[PO + CurrentLineOffset + 1] = SpectrumVURef_G;
                BmpRAW[PO + CurrentLineOffset + 2] = SpectrumVURef_R;
                PO += SpectrogramFullMaxW4;
            }
            for (I = (VUHeight - 1); I >= 0; I--)
            {
                BmpRAW[PO + CurrentLineOffset + 0] = SpectrumVUFil_B;
                BmpRAW[PO + CurrentLineOffset + 1] = SpectrumVUFil_G;
                BmpRAW[PO + CurrentLineOffset + 2] = SpectrumVUFil_R;
                PO += SpectrogramFullMaxW4;
            }

            if (SpectrogramDrawMode == 1)
            {
                PO -= ((SpectrogramFullMaxW4) * (VUHeight << 1));
                for (I = ((VUHeight << 1) - 1); I >= 0; I--)
                {
                    BmpRAW[PO2 + CurrentLineOffset2 + 0] = BmpRAW[PO + CurrentLineOffset + 0];
                    BmpRAW[PO2 + CurrentLineOffset2 + 1] = BmpRAW[PO + CurrentLineOffset + 1];
                    BmpRAW[PO2 + CurrentLineOffset2 + 2] = BmpRAW[PO + CurrentLineOffset + 2];

                    PO += SpectrogramFullMaxW4;
                    PO2 += SpectrogramFullMaxW4;
                }
            }
        }

        if ((DrawCurrent == 1) && ((SpectrogramDrawVU == 2) || (SpectrogramDrawVU == 3)))
        {
            // Drawing discrete signal states after filtration
            for (I = (VUHeight - 1); I >= 0; I--)
            {
                BmpRAW[PO + CurrentLineOffset + 0] = 0;
                BmpRAW[PO + CurrentLineOffset + 1] = 0;
                BmpRAW[PO + CurrentLineOffset + 2] = 0;
                if (SpectrumVUCalc & b00000001)
                {
                    BmpRAW[PO + CurrentLineOffset + 2] = 255;
                }
                if (SpectrumVUCalc & b00000010)
                {
                    BmpRAW[PO + CurrentLineOffset + 1] = 255;
                }
                PO += SpectrogramFullMaxW4;
            }

            // Drawing ultimate signal after including attack time and release time
            // and putting next following value to decoding
            if ((SpectrogramDisplayLines != DecodeBufferL) || (DispWidth != DecodeBufferW))
            {
                if (DecodeBufferT != 0)
                {
                    DELARR(volatile char, DecodeBuffer);
                }
                DecodeBufferT = SpectrogramDisplayLines * DispWidth;
                DecodeBuffer = NEWARR(volatile char, char[DecodeBufferT]);
                DecodeBufferL = SpectrogramDisplayLines;
                DecodeBufferW = DispWidth;
                ForceClear = true;
            }
            if (ForceClear)
            {
                for (I = 0; I < DecodeBufferT; I++)
                {
                    DecodeBuffer[I] = -1;
                }
            }
            int DecodePointer = (DispWidth * SpectrogramDisplayCurrentLine) + SpectrogramPointer;
            if (DecodeCorrection || (SpectrogramDrawMode == 2))
            {
                DecodeProcedure(DecodeBuffer[DecodePointer]);
                DecodeBuffer[DecodePointer] = (SpectrumVUCalc & b00000100);
            }
            else
            {
                DecodeBuffer[DecodePointer] = (SpectrumVUCalc & b00000100);
                DecodeProcedure(DecodeBuffer[DecodePointer]);
            }

            for (I = (VUHeight - 1); I >= 0; I--)
            {
                if (SpectrumVUCalc & b00000100)
                {
                    BmpRAW[PO + CurrentLineOffset + 0] = 255;
                    BmpRAW[PO + CurrentLineOffset + 1] = 255;
                    BmpRAW[PO + CurrentLineOffset + 2] = 255;
                }
                else
                {
                    BmpRAW[PO + CurrentLineOffset + 0] = 0;
                    BmpRAW[PO + CurrentLineOffset + 1] = 0;
                    BmpRAW[PO + CurrentLineOffset + 2] = 0;
                }
                PO += SpectrogramFullMaxW4;
            }

            if (SpectrogramDrawMode == 1)
            {
                PO -= ((SpectrogramFullMaxW4) * (VUHeight << 1));
                for (I = ((VUHeight << 1) - 1); I >= 0; I--)
                {
                    BmpRAW[PO2 + CurrentLineOffset2 + 0] = BmpRAW[PO + CurrentLineOffset + 0];
                    BmpRAW[PO2 + CurrentLineOffset2 + 1] = BmpRAW[PO + CurrentLineOffset + 1];
                    BmpRAW[PO2 + CurrentLineOffset2 + 2] = BmpRAW[PO + CurrentLineOffset + 2];

                    PO += SpectrogramFullMaxW4;
                    PO2 += SpectrogramFullMaxW4;
                }
            }
        }
    }

    SpectrogramPointer++;
    if (SpectrogramPointer >= DispWidth)
    {
        SpectrogramDisplayCurrentLine++;
        SpectrogramPointer = 0;
    }

    if (DrawCurrent == 1)
    {
        SpectrogramDisplayCurrentLine__ = SpectrogramDisplayCurrentLine;
        SpectrogramPointer__ = SpectrogramPointer;
    }
}

// Calculating spectrum of one sound
void AppCore::CalcSpectrum(short * BufInput, uchar * BufOutputR, uchar * BufOutputG, uchar * BufOutputB, bool CalcOver)
{
    int CalcSize = SpectrumResolutionFactor >> SpectrogramResolution;
    int ValueI;
    int BaseWorkI = SpectrogramBase * 1024;
    int OverPos = Settings_->OverloadThreshold;
    int OverNeg = 0 - Settings_->OverloadThreshold;
    try
    {
        for (int I = 0; I < CalcSize; I++)
        {
            SpectrogramRe[I] = BufInput[I];
            SpectrogramIm[I] = 0;
            if ((BufInput[I] > OverPos) || (BufInput[I] < OverNeg))
            {
               if (CalcOver)
               {
                   SpectrumBufOverload = true;
               }
            }
        }
        F.FFTW(SpectrogramRe, SpectrogramIm);
        int S = (CalcSize >> 1) - 1;
        for (int I = S; I >= 0; I--)
        {
            ValueI = F.Magnitude(SpectrogramRe[I], SpectrogramIm[I]) * SpectrogramAmp;
            ValueI -= BaseWorkI;
            if (ValueI > 70000)
            {
                ValueI = 70000;
            }
            else
            {
                if (ValueI < 0)
                {
                    ValueI = 0;
                }
            }

            BufOutputR[I] = SpectrogramGammaLUT_R[ValueI];
            BufOutputG[I] = SpectrogramGammaLUT_G[ValueI];
            BufOutputB[I] = SpectrogramGammaLUT_B[ValueI];
        }

        if (SpectrogramMinMax != 0)
        {
            int I_, I0, II_, II0;
            if (SpectrogramMinMax > 0)
            {
                I0 = S - SpectrogramMinMaxX + 1;
                for (I_ = (SpectrogramMinMaxX - 1); I_ >= 0; I_--)
                {
                    SpectrumTempMinMax_R[I_] = 0;
                    SpectrumTempMinMax_G[I_] = 0;
                    SpectrumTempMinMax_B[I_] = 0;
                    SpectrumTempMinMax_R[I0] = 0;
                    SpectrumTempMinMax_G[I0] = 0;
                    SpectrumTempMinMax_B[I0] = 0;
                    II0 = S;
                    for (II_ = (I_ + SpectrogramMinMaxX); II_ >= 0; II_--)
                    {
                        if (SpectrumTempMinMax_R[I_] < BufOutputR[II_]) { SpectrumTempMinMax_R[I_] = BufOutputR[II_]; }
                        if (SpectrumTempMinMax_G[I_] < BufOutputG[II_]) { SpectrumTempMinMax_G[I_] = BufOutputG[II_]; }
                        if (SpectrumTempMinMax_B[I_] < BufOutputB[II_]) { SpectrumTempMinMax_B[I_] = BufOutputB[II_]; }
                        if (SpectrumTempMinMax_R[I0] < BufOutputR[II0]) { SpectrumTempMinMax_R[I0] = BufOutputR[II0]; }
                        if (SpectrumTempMinMax_G[I0] < BufOutputG[II0]) { SpectrumTempMinMax_G[I0] = BufOutputG[II0]; }
                        if (SpectrumTempMinMax_B[I0] < BufOutputB[II0]) { SpectrumTempMinMax_B[I0] = BufOutputB[II0]; }
                        II0--;
                    }
                    I0++;
                }
                for (I_ = (S - SpectrogramMinMaxX); I_ >= SpectrogramMinMaxX; I_--)
                {
                    SpectrumTempMinMax_R[I_] = 0;
                    SpectrumTempMinMax_G[I_] = 0;
                    SpectrumTempMinMax_B[I_] = 0;
                    for (II_ = (I_ - SpectrogramMinMaxX); II_ <= (I_ + SpectrogramMinMaxX); II_++)
                    {
                        if (SpectrumTempMinMax_R[I_] < BufOutputR[II_]) { SpectrumTempMinMax_R[I_] = BufOutputR[II_]; }
                        if (SpectrumTempMinMax_G[I_] < BufOutputG[II_]) { SpectrumTempMinMax_G[I_] = BufOutputG[II_]; }
                        if (SpectrumTempMinMax_B[I_] < BufOutputB[II_]) { SpectrumTempMinMax_B[I_] = BufOutputB[II_]; }
                    }
                }
            }
            else
            {
                I0 = S - SpectrogramMinMaxX + 1;
                for (I_ = (SpectrogramMinMaxX - 1); I_ >= 0; I_--)
                {
                    SpectrumTempMinMax_R[I_] = 255;
                    SpectrumTempMinMax_G[I_] = 255;
                    SpectrumTempMinMax_B[I_] = 255;
                    SpectrumTempMinMax_R[I0] = 255;
                    SpectrumTempMinMax_G[I0] = 255;
                    SpectrumTempMinMax_B[I0] = 255;
                    II0 = S;
                    for (II_ = (I_ + SpectrogramMinMaxX); II_ >= 0; II_--)
                    {
                        if (SpectrumTempMinMax_R[I_] > BufOutputR[II_]) { SpectrumTempMinMax_R[I_] = BufOutputR[II_]; }
                        if (SpectrumTempMinMax_G[I_] > BufOutputG[II_]) { SpectrumTempMinMax_G[I_] = BufOutputG[II_]; }
                        if (SpectrumTempMinMax_B[I_] > BufOutputB[II_]) { SpectrumTempMinMax_B[I_] = BufOutputB[II_]; }
                        if (SpectrumTempMinMax_R[I0] > BufOutputR[II0]) { SpectrumTempMinMax_R[I0] = BufOutputR[II0]; }
                        if (SpectrumTempMinMax_G[I0] > BufOutputG[II0]) { SpectrumTempMinMax_G[I0] = BufOutputG[II0]; }
                        if (SpectrumTempMinMax_B[I0] > BufOutputB[II0]) { SpectrumTempMinMax_B[I0] = BufOutputB[II0]; }
                        II0--;
                    }
                    I0++;
                }
                for (I_ = (S - SpectrogramMinMaxX); I_ >= SpectrogramMinMaxX; I_--)
                {
                    SpectrumTempMinMax_R[I_] = 255;
                    SpectrumTempMinMax_G[I_] = 255;
                    SpectrumTempMinMax_B[I_] = 255;
                    for (II_ = (I_ - SpectrogramMinMaxX); II_ <= (I_ + SpectrogramMinMaxX); II_++)
                    {
                        if (SpectrumTempMinMax_R[I_] > BufOutputR[II_]) { SpectrumTempMinMax_R[I_] = BufOutputR[II_]; }
                        if (SpectrumTempMinMax_G[I_] > BufOutputG[II_]) { SpectrumTempMinMax_G[I_] = BufOutputG[II_]; }
                        if (SpectrumTempMinMax_B[I_] > BufOutputB[II_]) { SpectrumTempMinMax_B[I_] = BufOutputB[II_]; }
                    }
                }
            }
            for (int I = S; I >= 0; I--)
            {
                BufOutputR[I] = SpectrumTempMinMax_R[I];
                BufOutputG[I] = SpectrumTempMinMax_G[I];
                BufOutputB[I] = SpectrumTempMinMax_B[I];
            }
        }
    }
    catch(...)
    {

    }
}

// Generating gamma LUT to use with spectrogram drawing
void AppCore::SetGamma(bool Fullscreen)
{
    if (Settings_->DisplayGammaFull != Fullscreen)
    {
        Settings_->DisplayGammaFull = Fullscreen;
        Settings_->DisplayGammaUpdate = true;
    }
    if (!Settings_->DisplayGammaUpdate)
    {
        return;
    }

    int Gamma = Settings_->DisplayGamma;
    int SpectrumPaletteSelected = Settings_->SpectrumPaletteSelected;
    long double GammaX = Gamma;
    GammaX = GammaX / 1000.0L;
    GammaX = 1.0 / GammaX;


    llong * LUTR = NEWARR(llong, llong[70001]);
    llong * LUTG = NEWARR(llong, llong[70001]);
    llong * LUTB = NEWARR(llong, llong[70001]);

    int MaxStep = 65536;
    for (int I = 0; I <= 70000; I++)
    {
        LUTR[I] = Min(I, MaxStep);
        LUTG[I] = Min(I, MaxStep);
        LUTB[I] = Min(I, MaxStep);
    }


    if ((SpectrumPaletteSelected > 0) && (Settings_->SpectrumPaletteFile.size() >= (uint)SpectrumPaletteSelected))
    {
        int I = SpectrumPaletteSelected - 1;

        string FileName = Eden::ApplicationDirectory() + Settings_->SpectrumPaletteFile[I];
        QImage ImgF(FileName.c_str());
        int ImageWidth = ImgF.width();
        int ImageHeight = ImgF.height();
        uint ColorRGB;
        llong ColorR;
        llong ColorG;
        llong ColorB;

        int ImageX = Settings_->SpectrumPaletteColumn[I];
        int ImageY1 = Settings_->SpectrumPaletteLine1[I];
        int ImageY2 = Settings_->SpectrumPaletteLine2[I];
        if (ImageY2 < ImageY1)
        {
            ImageY1 = Settings_->SpectrumPaletteLine2[I];
            ImageY2 = Settings_->SpectrumPaletteLine1[I];
        }
        if ((ImageX < ImageWidth) && (ImageY2 < ImageHeight))
        {
            if ((ImageX >= 0) && (ImageY1 >= 0))
            {
                if (ImageY2 >= ImageY1)
                {
                    int VecSize = ImageY2 - ImageY1 + 1;

                    llong MaxStep_ = MaxStep - 1;
                    llong VecSize_ = VecSize - 1;
                    int I0 = 0;
                    bool Rev = (Settings_->SpectrumPaletteLine1[I] > Settings_->SpectrumPaletteLine2[I]);
                    for (I = 0; I < VecSize; I++)
                    {
                        if (Rev)
                        {
                            ColorRGB = ImgF.pixel(ImageX, ImageY2 - I);
                        }
                        else
                        {
                            ColorRGB = ImgF.pixel(ImageX, ImageY1 + I);
                        }
                        ColorR = (ColorRGB >> 16) & 255;
                        ColorG = (ColorRGB >> 8) & 255;
                        ColorB = (ColorRGB) & 255;

                        llong I_ = I;
                        I_ = I_ * (MaxStep_);
                        I_ = I_ / (VecSize_);

                        LUTR[I_] = ColorR * 257LL;
                        LUTG[I_] = ColorG * 257LL;
                        LUTB[I_] = ColorB * 257LL;

                        if (I_ > (I0 + 1))
                        {
                            llong R = I_ - I0;
                            llong T1, T2, C, T1X, T2X;
                            for (int II = (I0 + 1); II < I_; II++)
                            {
                                T1 = II - I0;
                                T2 = R - T1;
                                T1X = T1 * LUTR[I0];
                                T2X = T2 * LUTR[I_];
                                C = (T1X + T2X) / R;
                                LUTR[II] = C;
                                T1X = T1 * LUTG[I0];
                                T2X = T2 * LUTG[I_];
                                C = (T1X + T2X) / R;
                                LUTG[II] = C;
                                T1X = T1 * LUTB[I0];
                                T2X = T2 * LUTB[I_];
                                C = (T1X + T2X) / R;
                                LUTB[II] = C;
                            }
                        }
                        I0 = I_;
                    }




                }
            }
        }
    }

    for (int I = (MaxStep - 1); I <= 70000; I++)
    {
        LUTR[I] = LUTR[MaxStep - 1];
        LUTG[I] = LUTG[MaxStep - 1];
        LUTB[I] = LUTB[MaxStep - 1];
    }

    for (int I = 0; I <= 70000; I++)
    {
        long double I_R = LUTR[I];
        long double I_G = LUTG[I];
        long double I_B = LUTB[I];
        I_R = I_R / 65536.0L;
        I_G = I_G / 65536.0L;
        I_B = I_B / 65536.0L;
        I_R = powl(I_R, GammaX);
        I_G = powl(I_G, GammaX);
        I_B = powl(I_B, GammaX);
        I_R = I_R * 256.0L;
        I_G = I_G * 256.0L;
        I_B = I_B * 256.0L;
        int IX_R = I_R;
        int IX_G = I_G;
        int IX_B = I_B;
        SpectrogramGammaLUT_R[I] = Max(Min(IX_R, 255), 0);
        SpectrogramGammaLUT_G[I] = Max(Min(IX_G, 255), 0);
        SpectrogramGammaLUT_B[I] = Max(Min(IX_B, 255), 0);
    }

    DELARR(llong, LUTR);
    DELARR(llong, LUTG);
    DELARR(llong, LUTB);

    Settings_->DisplayGammaUpdate = false;
}

// Calculating volume of one sound
void AppCore::CalcVU(short * BufInput, uchar * BufOutput_R, uchar * BufOutput_G, uchar * BufOutput_B, short * BufOutputX)
{
    float VUVal = BufInput[0];
    VUVal *= VUAmp;
    int VUVal_ = (VUVal / 16384.0);
    if (VUVal_ < 0) { VUVal_ = 0; }
    if (VUVal_ > 511) { VUVal_ = 511; }
    BufOutputX[0] = VUVal_;

    VUVal_ = (VUVal / 64.0);
    if (VUVal_ < 0) { VUVal_ = 0; }
    if (VUVal_ > 70000) { VUVal_ = 70000; }
    BufOutput_R[0] = SpectrogramGammaLUT_R[VUVal_];
    BufOutput_G[0] = SpectrogramGammaLUT_G[VUVal_];
    BufOutput_B[0] = SpectrogramGammaLUT_B[VUVal_];
}

// Procedure invoked by timer tick
void AppCore::AudioTimerTrigger(uchar * SpectrogramRAW, int DispWidth, int DispHeight)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> T1 = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> T2;

    if (DispWidth > SpectrogramFullMaxW)
    {
        DispWidth = SpectrogramFullMaxW;
    }
    if (DispHeight > SpectrogramFullMaxH)
    {
        DispHeight = SpectrogramFullMaxH;
    }

    int CalcSize = SpectrumResolutionFactor >> SpectrogramResolution;
    int I, V1, V2, V3;

    bool NoFilter = !(Settings_->FiltersEnabled);

    if (Settings_->GeneratorRecalc)
    {
        MorseEncoderCore_.CalcPeriod(XFreqL, XFreqH);
        Settings_->GeneratorRecalc = false;
    }

    bool RedrawAllowed = true;
    bool SpectrogramLoopWork = (AudioRaw.Count >= CalcSize) && (AudioFil.Count >= CalcSize) && (AudioCalcVU.Count >= SpectrogramStep);


    // Calculating draw decimation value
    uint CalcDecimationCounterMax = 1;
    if (Settings_->CalcDecimationConst)
    {
        CalcDecimationCounterMax = Settings_->CalcDecimation;
    }
    else
    {
        CalcDecimationCounterMax = (Settings_->CalcDecimation << 3) / SpectrogramStep;
    }
    if (CalcDecimationCounterMax < 1)
    {
        CalcDecimationCounterMax = 1;
    }


    // Spectrogram repainting if current spectrogram is not painting
    if (!SpectrogramLoopWork)
    {
        // Spectrogram repainting
        if ((DispHeightLast != DispHeight) || (DispWidthLast != DispWidth) || (Settings_->WholeRepaint))
        {
            Settings_->WholeRepaint = false;
            WholeRepaint = 1;
        }
        if (WholeRepaint > 0)
        {
            if (WholeRepaint < 3)
            {
                if (RepaintBufL > 0)
                {
                    if (RedrawAllowed)
                    {
                        RedrawAllowed = false;
                        AudioTempRaw_ = NEWARR(short, short[CalcSize << 1]);
                        AudioTempFil_ = NEWARR(short, short[CalcSize << 1]);
                        AudioTempRef_ = NEWARR(short, short[CalcSize << 1]);

                        if (WholeRepaint == 1)
                        {
                            WholeRepaintOffset = 0;
                            WholeRepaint = 2;
                        }
                        int T0;
                        int MaxOffset = Min(RepaintBufL, (SpectrogramDisplayLines * DispWidth) - Settings_->SpectrogramStrip + 1);
                        bool Work = true;
                        int CalcDecimationCounterX = (CalcDecimationCounter % CalcDecimationCounterMax) - CalcDecimationCounterMax;
                        while (Work)
                        {
                            int RepaintBufOffset = (WholeRepaintOffset - 1 + CalcDecimationCounterMax) * SpectrogramStep;
                            RepaintBufRaw->Last(AudioTempRaw_, RepaintBufOffset, CalcSize);
                            RepaintBufFil->Last(AudioTempFil_, RepaintBufOffset, CalcSize);
                            RepaintBufRef->Last(AudioTempRef_, RepaintBufOffset, CalcSize);


                            SpectrumBufOverload = false;
                            if (NoFilter)
                            {
                                CalcSpectrum(AudioTempFil_, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
                            }
                            else
                            {
                                CalcSpectrum(AudioTempRaw_, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
                                if (Settings_->DrawFil)
                                {
                                    CalcSpectrum(AudioTempFil_, SpectrumBufFil_R, SpectrumBufFil_G, SpectrumBufFil_B, false);
                                }

                                if (Settings_->DrawRef)
                                {
                                    CalcSpectrum(AudioTempRef_, SpectrumBufRef_R, SpectrumBufRef_G, SpectrumBufRef_B, false);
                                }
                            }

                            CalcDecimationCounterX += CalcDecimationCounterMax;
                            while (CalcDecimationCounterX > 0)
                            {
                                if (WholeRepaintOffset < MaxOffset)
                                {
                                    RepaintFilVU->Last(AudioTempFil_, RepaintBufOffset - 1 + SpectrogramStep, 1);
                                    CalcVU(AudioTempFil_, &SpectrumVUFil_R, &SpectrumVUFil_G, &SpectrumVUFil_B, &SpectrumVUFilX);
                                    RepaintRefVU->Last(AudioTempRef_, RepaintBufOffset - 1 + SpectrogramStep, 1);
                                    CalcVU(AudioTempRef_, &SpectrumVURef_R, &SpectrumVURef_G, &SpectrumVURef_B, &SpectrumVURefX);
                                    SpectrogramGet(SpectrogramRAW, DispWidth, DispHeight, 0, WholeRepaintOffset + 1);
                                }
                                CalcDecimationCounterX--;
                                WholeRepaintOffset++;
                            }

                            T2 = std::chrono::high_resolution_clock::now();
                            T0 = std::chrono::duration<double, std::milli>(T2-T1).count();
                            if (WholeRepaintOffset >= MaxOffset)
                            {
                                Work = false;
                                WholeRepaint = 3;
                                SpectrogramGet(SpectrogramRAW, DispWidth, DispHeight, 2, 1);
                            }
                            else
                            {
                                if ((T0 > WholeRepaintTimeout))
                                {
                                    Work = false;
                                    SpectrogramGet(SpectrogramRAW, DispWidth, DispHeight, 2, 1);
                                }
                            }
                        }

                        DELARR(short, AudioTempRaw_);
                        DELARR(short, AudioTempFil_);
                        DELARR(short, AudioTempRef_);
                    }
                }
                else
                {
                    WholeRepaint = 0;
                }
            }
        }
    }

    while (SpectrogramLoopWork)
    {
        int BufGetCount = Max(CalcSize, SpectrogramStep);
        if (NoFilter)
        {
            AudioRaw.Get(SpectrogramStep);
            AudioFil.First(AudioTempFil, BufGetCount);
            AudioFil.Get(SpectrogramStep);
            AudioRef.Get(SpectrogramStep);
        }
        else
        {
            AudioRaw.First(AudioTempRaw, BufGetCount);
            AudioRaw.Get(SpectrogramStep);
            AudioFil.First(AudioTempFil, BufGetCount);
            AudioFil.Get(SpectrogramStep);
            AudioRef.First(AudioTempRef, BufGetCount);
            AudioRef.Get(SpectrogramStep);
        }
        RepaintBufRaw->Put(AudioTempRaw, SpectrogramStep);
        RepaintBufFil->Put(AudioTempFil, SpectrogramStep);
        RepaintBufRef->Put(AudioTempRef, SpectrogramStep);

        if (CalcDecimationCounter >= CalcDecimationCounterMax)
        {
            // Spectrogram repainting
            if ((DispHeightLast != DispHeight) || (DispWidthLast != DispWidth) || (Settings_->WholeRepaint))
            {
                Settings_->WholeRepaint = false;
                WholeRepaint = 1;
            }
            if (WholeRepaint > 0)
            {
                if (RepaintBufL > 0)
                {
                    if (RedrawAllowed)
                    {
                        RedrawAllowed = false;
                        AudioTempRaw_ = NEWARR(short, short[CalcSize << 1]);
                        AudioTempFil_ = NEWARR(short, short[CalcSize << 1]);
                        AudioTempRef_ = NEWARR(short, short[CalcSize << 1]);

                        if (WholeRepaint == 1)
                        {
                            WholeRepaintOffset = 0;
                            WholeRepaint = 2;
                        }
                        else
                        {
                            if (WholeRepaint == 3)
                            {
                                WholeRepaintOffset = 0;
                                WholeRepaint = 0;
                            }
                        }
                        int T0;
                        int MaxOffset = Min(RepaintBufL, (SpectrogramDisplayLines * DispWidth) - Settings_->SpectrogramStrip);
                        bool Work = true;
                        int CalcDecimationCounterX;
                        while (Work)
                        {
                            int RepaintBufOffset = WholeRepaintOffset * SpectrogramStep;
                            RepaintBufRaw->Last(AudioTempRaw_, RepaintBufOffset, CalcSize);
                            RepaintBufFil->Last(AudioTempFil_, RepaintBufOffset, CalcSize);
                            RepaintBufRef->Last(AudioTempRef_, RepaintBufOffset, CalcSize);


                            SpectrumBufOverload = false;
                            if (NoFilter)
                            {
                                CalcSpectrum(AudioTempFil_, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
                            }
                            else
                            {
                                CalcSpectrum(AudioTempRaw_, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
                                if (Settings_->DrawFil)
                                {
                                    CalcSpectrum(AudioTempFil_, SpectrumBufFil_R, SpectrumBufFil_G, SpectrumBufFil_B, false);
                                }

                                if (Settings_->DrawRef)
                                {
                                    CalcSpectrum(AudioTempRef_, SpectrumBufRef_R, SpectrumBufRef_G, SpectrumBufRef_B, false);
                                }
                            }

                            CalcDecimationCounterX = CalcDecimationCounterMax;
                            while (CalcDecimationCounterX > 0)
                            {
                                if (WholeRepaintOffset < MaxOffset)
                                {
                                    RepaintFilVU->Last(AudioTempFil_, RepaintBufOffset - 1, 1);
                                    CalcVU(AudioTempFil_, &SpectrumVUFil_R, &SpectrumVUFil_G, &SpectrumVUFil_B, &SpectrumVUFilX);
                                    RepaintRefVU->Last(AudioTempRef_, RepaintBufOffset - 1, 1);
                                    CalcVU(AudioTempRef_, &SpectrumVURef_R, &SpectrumVURef_G, &SpectrumVURef_B, &SpectrumVURefX);
                                    SpectrogramGet(SpectrogramRAW, DispWidth, DispHeight, 0, WholeRepaintOffset - CalcDecimationCounterMax + 1);
                                }
                                CalcDecimationCounterX--;
                                WholeRepaintOffset++;
                            }

                            T2 = std::chrono::high_resolution_clock::now();
                            T0 = std::chrono::duration<double, std::milli>(T2-T1).count();
                            if (WholeRepaintOffset >= MaxOffset)
                            {
                                Work = false;
                                WholeRepaint = 0;
                            }
                            else
                            {
                                if ((T0 > WholeRepaintTimeout))
                                {
                                    Work = false;
                                }
                            }
                        }

                        DELARR(short, AudioTempRaw_);
                        DELARR(short, AudioTempFil_);
                        DELARR(short, AudioTempRef_);
                    }
                }
                else
                {
                    WholeRepaint = 0;
                }
            }


            RepaintBufRaw->Last(AudioTempRaw, 0, CalcSize);
            RepaintBufFil->Last(AudioTempFil, 0, CalcSize);
            RepaintBufRef->Last(AudioTempRef, 0, CalcSize);


            SpectrumBufOverload = false;
            CalcDecimationCounter = 0;
            if (NoFilter)
            {
                CalcSpectrum(AudioTempFil, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
            }
            else
            {
                CalcSpectrum(AudioTempRaw, SpectrumBufRaw_R, SpectrumBufRaw_G, SpectrumBufRaw_B, true);
                if (Settings_->DrawFil)
                {
                    CalcSpectrum(AudioTempFil, SpectrumBufFil_R, SpectrumBufFil_G, SpectrumBufFil_B, false);
                }

                if (Settings_->DrawRef)
                {
                    CalcSpectrum(AudioTempRef, SpectrumBufRef_R, SpectrumBufRef_G, SpectrumBufRef_B, false);
                }
            }
        }
        CalcDecimationCounter++;


        AudioFilVU.First(AudioTempFil, SpectrogramStep);
        RepaintFilVU->Put(AudioTempFil, SpectrogramStep);
        AudioFilVU.Get(SpectrogramStep);
        CalcVU(AudioTempFil, &SpectrumVUFil_R, &SpectrumVUFil_G, &SpectrumVUFil_B, &SpectrumVUFilX);

        AudioRefVU.First(AudioTempRef, SpectrogramStep);
        RepaintRefVU->Put(AudioTempRef, SpectrogramStep);
        AudioRefVU.Get(SpectrogramStep);
        CalcVU(AudioTempRef, &SpectrumVURef_R, &SpectrumVURef_G, &SpectrumVURef_B, &SpectrumVURefX);

        AudioCalcVU.Get(AudioTempX, SpectrogramStep);
        V1 = 0;
        V2 = 0;
        V3 = 0;
        I = SpectrogramStep - 1;
        while (I >= 0)
        {
            V1 += (AudioTempX[I] & b00000001);
            V2 += (AudioTempX[I] & b00000010);
            V3 += (AudioTempX[I] & b00000100);
            I--;
        }
        V1 = V1 << 1;
        V3 = V3 >> 1;
        SpectrumVUCalc = 0;
        if (V1 >= SpectrogramStep) { SpectrumVUCalc += 1; }
        if (V2 >= SpectrogramStep) { SpectrumVUCalc += 2; }
        if (V3 >= SpectrogramStep) { SpectrumVUCalc += 4; }


        // Painting current spectrogram
        SpectrogramGet(SpectrogramRAW, DispWidth, DispHeight, 1, 0);

        SpectrogramLoopWork = (AudioRaw.Count >= CalcSize) && (AudioFil.Count >= CalcSize) && (AudioCalcVU.Count >= SpectrogramStep);
    }
}

void AppCore::CreateFilter(llong * FilterRaw, double FilterLf, double FilterHf)
{
    int I;

    double F1_, F1__, F2_, F2__, FilterValue;
    F1_ = 2.0 * FilterLf;
    F1__ = 2.0 * FilterLf * M_PIx;
    F2_ = 2.0 * FilterHf;
    F2__ = 2.0 * FilterHf * M_PIx;

    if (FilterLf == FilterHf)
    {
        // Blank filter
        for (I = 0; I < FilterSize; I++)
        {
            FilterRaw[I] = 0;
        }
        return;
    }

    if (FilterLf == 0)
    {
        // Low pass filter
        FilterValue = F2_;
        FilterValue *= WindowAmplitude;
        FilterRaw[0] = FilterValue;
        for (I = 1; I < FilterSize; I++)
        {
            double I_ = I;
            FilterValue = (F2_ * (sin(F2__ * I_) / (F2__ * I_)));

            double T1 = ((FilterSize - 1) - I);
            double T2 = (FilterSize * 2 - 2);

            // Blackman window
            FilterValue = FilterValue * ((0.42 - 0.5 * cos(2 * M_PIx * (T1 / T2))) + (0.08 * cos(4 * M_PIx * (T1 / T2))));

            // Hamming window
            //FilterValue = FilterValue * (0.54 - 0.46 * cos(2 * M_PIx * (T1 / T2)));

            FilterValue *= WindowAmplitude;
            FilterRaw[I] = FilterValue;
        }
        return;
    }

    if (FilterHf == 0.5)
    {
        // High pass filter
        FilterValue = 1.0 - F1_;
        FilterValue *= WindowAmplitude;
        FilterRaw[0] = FilterValue;
        for (I = 1; I < FilterSize; I++)
        {
            double I_ = I;
            FilterValue = 0.0 - (F1_ * (sin(F1__ * I_) / (F1__ * I_)));

            double T1 = ((FilterSize - 1) - I);
            double T2 = (FilterSize * 2 - 2);

            // Blackman window
            FilterValue = FilterValue * ((0.42 - 0.5 * cos(2 * M_PIx * (T1 / T2))) + (0.08 * cos(4 * M_PIx * (T1 / T2))));

            // Hamming window
            //FilterValue = FilterValue * (0.54 - 0.46 * cos(2 * M_PIx * (T1 / T2)));

            FilterValue *= WindowAmplitude;
            FilterRaw[I] = FilterValue;
        }
        return;
    }

    // Band pass filter
    FilterValue = F2_ - F1_;
    FilterValue *= WindowAmplitude;
    FilterRaw[0] = FilterValue;
    for (I = 1; I < FilterSize; I++)
    {
        double I_ = I;
        FilterValue = (F2_ * (sin(F2__ * I_) / (F2__ * I_))) - (F1_ * (sin(F1__ * I_) / (F1__ * I_)));

        double T1 = ((FilterSize - 1) - I);
        double T2 = (FilterSize * 2 - 2);

        // Blackman window
        FilterValue = FilterValue * ((0.42 - 0.5 * cos(2 * M_PIx * (T1 / T2))) + (0.08 * cos(4 * M_PIx * (T1 / T2))));

        // Hamming window
        //FilterValue = FilterValue * (0.54 - 0.46 * cos(2 * M_PIx * (T1 / T2)));

        FilterValue *= WindowAmplitude;
        FilterRaw[I] = FilterValue;
    }
}

bool AppCore::BufOpen(int SR)
{
    if (RepaintBufRaw != NULL)
    {
        DEL(RingBuffer<short>, RepaintBufRaw);
        DEL(RingBuffer<short>, RepaintBufFil);
        DEL(RingBuffer<short>, RepaintBufRef);
        DEL(RingBuffer<short>, RepaintFilVU);
        DEL(RingBuffer<short>, RepaintRefVU);
        RepaintBufRaw = NULL;
        RepaintBufFil = NULL;
        RepaintBufRef = NULL;
        RepaintFilVU = NULL;
        RepaintRefVU = NULL;
    }
    RepaintBufL = Settings_->RepaintBufferSize;
    WholeRepaintTimeout = Settings_->RepaintTimeout;
    if (RepaintBufL > 0)
    {
        RepaintBufRaw = NEW(RingBuffer<short>, RingBuffer<short>());
        RepaintBufFil = NEW(RingBuffer<short>, RingBuffer<short>());
        RepaintBufRef = NEW(RingBuffer<short>, RingBuffer<short>());
        RepaintFilVU = NEW(RingBuffer<short>, RingBuffer<short>());
        RepaintRefVU = NEW(RingBuffer<short>, RingBuffer<short>());
        RepaintBufRaw->Init(RepaintBufL);
        RepaintBufFil->Init(RepaintBufL);
        RepaintBufRef->Init(RepaintBufL);
        RepaintFilVU->Init(RepaintBufL);
        RepaintRefVU->Init(RepaintBufL);
    }

    PlaybackCompensationCounter = 0;
    BufSampleRate = SR;
    BufOffset = 0;
    BufPos = 0;
    BufSize = 0;
    BufTime = 0;
    int I = 0;
    bool FExists = true;
    string FN = "";
    if (AudioFileBufferSession)
    {
        while (FExists)
        {
            I++;
            FN = Eden::ToStr(I);
            while (FN.length() < 5) { FN = "0" + FN; }
            FN = Settings_->GetRecordFileName() + FN + ".wav";
            FExists = Eden::FileExists(FN);
        }
        return BufFile.FileNew(FN, SR, true, false);
    }
    else
    {
        return true;
    }
}

void AppCore::BufClose()
{
    if (RepaintBufRaw != NULL)
    {
        DEL(RingBuffer<short>, RepaintBufRaw);
        DEL(RingBuffer<short>, RepaintBufFil);
        DEL(RingBuffer<short>, RepaintBufRef);
        DEL(RingBuffer<short>, RepaintFilVU);
        DEL(RingBuffer<short>, RepaintRefVU);
        RepaintBufL = 0;
        RepaintBufRaw = NULL;
        RepaintBufFil = NULL;
        RepaintBufRef = NULL;
        RepaintFilVU = NULL;
        RepaintRefVU = NULL;
    }

    BufTime = 0;
    if (AudioFileBufferSession)
    {
        BufFile.FileClose();
    }
}

void AppCore::ProcessAudio(short *Buf, int N0)
{
    if (AudioFileBufferSession)
    {
        // Putting current data to buffer
        BufFile.WriteM(Buf, BufSize, N0);
        BufSize += N0;

        // Getting data from buffer against offset and speed
        int N = (N0 * BufSpeed) / 100;
        if (N > (BufSize - BufOffset))
        {
            N = (BufSize - BufOffset);
        }
        BufFile.ReadM(Buf, BufOffset, N);
        BufOffset += N;
        BufTime = (BufSize - BufOffset) / BufSampleRate;

        // Putting to processing buffer
        AudioSrc.Put(Buf, N);
    }
    else
    {
        if (ReplayBufferL > 0)
        {
            int T = 0;
            int ReplayBufferP_ = ReplayBufferP;
            while (T < N0)
            {
                ReplayBuffer[ReplayBufferP_] = Buf[T];
                ReplayBufferP_++;
                if (ReplayBufferP_ >= ReplayBufferL)
                {
                    ReplayBufferP_ -= ReplayBufferL;
                }
                T++;
            }
            T = 0;
            if (ReplayBufferF < ReplayBufferL)
            {
                ReplayBufferF += N0;
                if (ReplayBufferF > ReplayBufferL)
                {
                    ReplayBufferF = ReplayBufferL;
                }
            }
            int ReplayBufferPX = ReplayBufferP - BufOffset;

            int N = (N0 * BufSpeed) / 100;
            if (N > (N0 + BufOffset))
            {
                N = (N0 + BufOffset);
            }
            BufOffset += (N0 - N);
            if (BufOffset > ReplayBufferL)
            {
                BufOffset = ReplayBufferL;
            }
            if (BufOffset < 0)
            {
                BufOffset = 0;
            }
            BufTime = BufOffset / BufSampleRate;

            while (T < N)
            {
                Buf[T] = ReplayBuffer[ReplayBufferPX];
                ReplayBufferPX++;
                if (ReplayBufferPX >= ReplayBufferL)
                {
                    ReplayBufferPX -= ReplayBufferL;
                }
                T++;
            }
            ReplayBufferP = ReplayBufferP_;

            AudioSrc.Put(Buf, N);
        }
        else
        {
            AudioSrc.Put(Buf, N0);
        }
    }


    QTime ty;
    ty.start();

    // Processing buffer
    llong TempFil;
    llong XXXFil;
    llong TempRef;
    llong XXXRef;
    while (AudioSrc.Count > 0)
    {
        short AudioSrcSample = AudioSrc.GetOne();
        if (Settings_->FiltersEnabled)
        {
            FilterWindowWork[WindowPointer] = AudioSrcSample;
            //FilterWindowWork[WindowPointer] = rand() * 5;

            WindowPointer1 = WindowPointer - FilterSize - 0;
            if (WindowPointer1 < 0) { WindowPointer1 += FilterWindowWorkSize; }

            WindowPointer2 = WindowPointer1;

            AudioRaw.PutOne(FilterWindowWork[WindowPointer1]);
            TempFil = FilterWindowWork[WindowPointer1];
            XXXFil = (TempFil * FilterWindow[0]);
            TempRef = FilterWindowWork[WindowPointer1];
            XXXRef = (TempRef * FilterWindowRef[0]);


            WindowPointer1++;
            if (WindowPointer1 == FilterWindowWorkSize) { WindowPointer1 = 0; }
            if (WindowPointer2 == 0) { WindowPointer2 = FilterWindowWorkSize; }
            WindowPointer2--;
            for (int II = 1; II < FilterSize; II++)
            {
                TempFil = FilterWindowWork[WindowPointer1];
                XXXFil = XXXFil + (TempFil * FilterWindow[II]);
                TempRef = FilterWindowWork[WindowPointer1];
                XXXRef = XXXRef + (TempRef * FilterWindowRef[II]);
                TempFil = FilterWindowWork[WindowPointer2];
                XXXFil = XXXFil + (TempFil * FilterWindow[II]);
                TempRef = FilterWindowWork[WindowPointer2];
                XXXRef = XXXRef + (TempRef * FilterWindowRef[II]);

                WindowPointer1++;
                if (WindowPointer1 == FilterWindowWorkSize) { WindowPointer1 = 0; }
                if (WindowPointer2 == 0) { WindowPointer2 = FilterWindowWorkSize; }
                WindowPointer2--;
            }

            XXXFil = XXXFil / (WindowAmplitude);
            if (XXXFil > 32767) { XXXFil = 32767; }
            if (XXXFil < -32768) { XXXFil = -32768; }
            FilterWindowWorkFil[WindowPointer] = XXXFil;
            AudioFil.PutOne(XXXFil);

            XXXRef = XXXRef / (WindowAmplitude);
            if (XXXRef > 32767) { XXXRef = 32767; }
            if (XXXRef < -32768) { XXXRef = -32768; }
            FilterWindowWorkRef[WindowPointer] = XXXRef;
            AudioRef.PutOne(XXXRef);

            if (Settings_->PlaybackMode == 1)
            {
                AudioPlaybackBuf.PutOne(AudioSrcSample);
            }
            if (Settings_->PlaybackMode == 2)
            {
                AudioPlaybackBuf.PutOne(XXXFil);
            }
            if (Settings_->PlaybackMode == 3)
            {
                AudioPlaybackBuf.PutOne(XXXRef);
            }
        }
        else
        {
            AudioRaw.PutOne(AudioSrcSample);
            AudioFil.PutOne(AudioSrcSample);
            AudioRef.PutOne(AudioSrcSample);
            AudioPlaybackBuf.PutOne(AudioSrcSample);
            FilterWindowWork[WindowPointer] = AudioSrcSample;
            FilterWindowWorkFil[WindowPointer] = AudioSrcSample;
            FilterWindowWorkRef[WindowPointer] = AudioSrcSample;
        }




        if (VUMode == 0)
        {
            // Calculating average
            XXXFil = 0;
            XXXRef = 0;
            WindowPointer2 = WindowPointer;
            for (int II = 0; II < VUSize; II++)
            {
                if (FilterWindowWorkFil[WindowPointer2] >= 0)
                {
                    XXXFil += FilterWindowWorkFil[WindowPointer2];
                }
                else
                {
                    XXXFil -= FilterWindowWorkFil[WindowPointer2];
                }
                if (FilterWindowWorkRef[WindowPointer2] >= 0)
                {
                    XXXRef += FilterWindowWorkRef[WindowPointer2];
                }
                else
                {
                    XXXRef -= FilterWindowWorkRef[WindowPointer2];
                }
                if (WindowPointer2 == 0) { WindowPointer2 = FilterWindowWorkSize; }
                WindowPointer2--;
            }
            XXXFil /= VUSize;
            XXXRef /= VUSize;
        }
        else
        {
            if (VUMode == 1)
            {
                // Copying array
                WindowPointer2 = WindowPointer;
                for (int II = 0; II < VUSize; II++)
                {
                    VUMedianArrayFil[II] = Abs(FilterWindowWorkFil[WindowPointer2]);
                    VUMedianArrayRef[II] = Abs(FilterWindowWorkRef[WindowPointer2]);
                    if (WindowPointer2 == 0) { WindowPointer2 = FilterWindowWorkSize; }
                    WindowPointer2--;
                }

                // Calculating median
                int m, ip, ik, v, i, j, x;
                m = VUSize >> 1;
                ip = 0;
                ik = VUSize - 1;
                for(;;)
                {
                    v = VUMedianArrayFil[ip];
                    i = ip;
                    j = ik + 1;
                    while(i < j)
                    {
                        while(VUMedianArrayFil[++i] < v) ;
                        while(VUMedianArrayFil[--j] > v) ;
                        if(i < j)
                        {
                            x = VUMedianArrayFil[i];
                            VUMedianArrayFil[i] = VUMedianArrayFil[j];
                            VUMedianArrayFil[j] = x;
                        }
                    }
                    VUMedianArrayFil[ip] = VUMedianArrayFil[j];
                    VUMedianArrayFil[j] = v;
                    if(m == j) break;
                    if(m < j)
                    {
                        ik = j - 1;
                    }
                    else
                    {
                        ip = j + 1;
                    }
                }
                XXXFil = VUMedianArrayFil[m];
                m = VUSize >> 1;
                ip = 0;
                ik = VUSize - 1;
                for(;;)
                {
                    v = VUMedianArrayRef[ip];
                    i = ip;
                    j = ik + 1;
                    while(i < j)
                    {
                        while(VUMedianArrayRef[++i] < v) ;
                        while(VUMedianArrayRef[--j] > v) ;
                        if(i < j)
                        {
                            x = VUMedianArrayRef[i];
                            VUMedianArrayRef[i] = VUMedianArrayRef[j];
                            VUMedianArrayRef[j] = x;
                        }
                    }
                    VUMedianArrayRef[ip] = VUMedianArrayRef[j];
                    VUMedianArrayRef[j] = v;
                    if(m == j) break;
                    if(m < j)
                    {
                        ik = j - 1;
                    }
                    else
                    {
                        ip = j + 1;
                    }
                }
                XXXRef = VUMedianArrayRef[m];
            }
            else
            {
                // Calcaulating peak value
                XXXFil = 0;
                XXXRef = 0;
                WindowPointer2 = WindowPointer;
                int C;
                for (int II = 0; II < VUSize; II++)
                {
                    C = Abs(FilterWindowWorkFil[WindowPointer2]);
                    if (XXXFil < C)
                    {
                        XXXFil = C;
                    }
                    C = Abs(FilterWindowWorkRef[WindowPointer2]);
                    if (XXXRef < C)
                    {
                        XXXRef = C;
                    }
                    if (WindowPointer2 == 0) { WindowPointer2 = FilterWindowWorkSize; }
                    WindowPointer2--;
                }
            }
        }


        if ((MorseEncoderCore_.TransmitStateI > 0) && (Settings_->MuteTransmit))
        {
            MorseEncoderCore_.TransmitStateI--;
            XXXFil = 0;
            XXXRef = 0;
        }


        AudioFilVU.PutOne(XXXFil);
        AudioRefVU.PutOne(XXXRef);
        if (WithRef)
        {
            VUCalcFil = XXXFil;
            VUCalcRef = XXXRef;
            if (XXXRef == 0)
            {
                if (XXXFil > 0)
                {
                    VUCalc = 9999;
                }
                else
                {
                    VUCalc = 0;
                }
            }
            else
            {
                VUCalc = VUCalcFil / VUCalcRef;
            }

            // Recalculating to get that value 1 means 10 time difference,
            // so 1/10 of half of maximum trigger threshold
            VUCalc = VUCalc * 0.25;
        }
        else
        {
            VUCalc = XXXFil;
            VUCalc *= VUAmp;

            // Half of maximum trigger threshold
            VUCalc *= 2.5;

            // The same, as to display VU
            VUCalc /= 4194304.0;
            //VUCalc /= 16384.0;
            //VUCalc /= 256.0;
        }

        short CalVal = 0;
        if (VUCalc >= VUCalcAttackThreshold)
        {
            CalVal += 1;
        }
        if (VUCalc < VUCalcDecayThreshold)
        {
            CalVal += 2;
        }

        if ((CalVal & b00000011) != b00000011)
        {
            if (!VUCalcAttackState)
            {
                if (CalVal & b00000001)
                {
                    VUCalcAttackI++;
                    if (VUCalcAttackI >= VUCalcAttackL)
                    {
                        VUCalcAttackState = true;
                        VUCalcAttackI = 0;
                    }
                }
                else
                {
                    VUCalcAttackI = 0;
                }
            }
            else
            {
                if (CalVal & b00000010)
                {
                    VUCalcDecayI++;
                    if (VUCalcDecayI >= VUCalcDecayL)
                    {
                        VUCalcAttackState = false;
                        VUCalcDecayI = 0;
                    }
                }
                else
                {
                    VUCalcDecayI = 0;
                }
            }
        }



        if (VUCalcAttackState)
        {
            CalVal += 4;
        }
        AudioCalcVU.PutOne(CalVal);

        WindowPointer++;
        if (WindowPointer >= FilterWindowWorkSize) { WindowPointer = 0; }
    }
}

void AppCore::FileAudioLoad(string FileName)
{
    FileAudioPointer = 0;
    DELARR(short, FileAudioData);
    if (WF.FileOpen(FileName, true))
    {
        FileAudioLength = WF.Length;
        FileAudioData = NEWARR(short, short[FileAudioLength]);
        WF.ReadM(FileAudioData, 0, FileAudioLength);
        WF.FileClose();
    }
    else
    {
        FileAudioLength = 1;
        FileAudioData = NEWARR(short, short[1]);
    }
}

// Mouse event on spectrogram
void AppCore::MouseOperation(int Btn, int X, int Y, uchar * SpectrogramPicture)
{
    int MaxHeight = SpectrogramDrawLineWidth * SpectrogramDisplayLines;
    if (SpectrogramDrawMode == 1)
    {
        MaxHeight = SpectrogramDrawLineWidth * SpectrogramDisplayLines * 2;
    }


    if ((X < 0) || (Y < 0) || (X >= DispWidthLast) || (Y >= MaxHeight))
    {
        return;
    }

    if ((Btn == 1) || (Btn == 2) || (Btn == 4))
    {
        if (!MousePressed)
        {
            MouseX = X;
            MouseY = Y;
            MousePressed = true;
        }

        bool ClickSpectrogram = true;
        bool ClickAbove = false;
        bool ClickBelow = false;
        int MouseLinePosition = Y % SpectrogramDrawLineWidth;
        int MouseLineNumber = Y / SpectrogramDrawLineWidth;
        int SpectrogramPosition_;
        int SpectrogramSizeX;

        // Determining, which part of spectrogram was clicked
        if (SpectrogramVolumeBarSize > 0)
        {
            if (MouseLinePosition > (SpectrogramDrawLineWidth - SpectrogramVolumeBarSize))
            {
                ClickSpectrogram = false;
                ClickBelow = true;
            }
        }
        if (ClickSpectrogram)
        {
            SpectrogramSizeX = 1 << (SpectrogramZoom + 9);

            SpectrogramPosition_ = (SpectrogramDrawLineWidth - SpectrogramVolumeBarSize) - (MouseLinePosition - Shl(SpectrogramOffset, SpectrogramZoom - 1));

            if (SpectrogramPosition_ >= SpectrogramSizeX)
            {
                ClickAbove = true;
                ClickSpectrogram = false;
            }
        }

        if (((MouseMode == 0) || (MouseMode == 1)) && (!SpectrogramDrawVolume))
        {
            // Spectrogram clicked - setting filter
            if (ClickSpectrogram)
            {
                double SpectrogramPosition_D = SpectrogramPosition_;
                double SpectrogramSizeXD = SpectrogramSizeX * 2;
                double Val = SpectrogramPosition_D / SpectrogramSizeXD;
                double MinVal = 0;
                double MaxVal = 0.5;
                Val = Min(Max(Val, MinVal), MaxVal);

                if (Btn == 4)
                {
                    SpectrogramFilterMoveBand = !SpectrogramFilterMoveBand;
                }
                if (SpectrogramFilterMoveBand)
                {
                    if (Btn == 1)
                    {
                        double XFreqDelta = ((XFreqH + XFreqL) / 2.0) - Val;
                        XFreqL = XFreqL - XFreqDelta;
                        XFreqH = XFreqH - XFreqDelta;
                        if (XFreqL < 0)
                        {
                            XFreqH = XFreqH + XFreqL;
                            XFreqL = 0;
                        }
                        if (XFreqH > 0.5)
                        {
                            XFreqL = XFreqL + (XFreqH - 0.5);
                            XFreqH = 0.5;
                        }
                        CreateFilter(FilterWindow, XFreqL, XFreqH);
                        MorseEncoderCore_.CalcPeriod(XFreqL, XFreqH);
                        XFreqL__ = XFreqL * ((double)SpectrumLines) * 2.0;
                        XFreqH__ = XFreqH * ((double)SpectrumLines) * 2.0;
                    }
                    if (Btn == 2)
                    {
                        double XFreqDelta = ((XFreqHRef + XFreqLRef) / 2.0) - Val;
                        XFreqLRef = XFreqLRef - XFreqDelta;
                        XFreqHRef = XFreqHRef - XFreqDelta;
                        if (XFreqLRef < 0)
                        {
                            XFreqHRef = XFreqHRef + XFreqLRef;
                            XFreqLRef = 0;
                        }
                        if (XFreqHRef > 0.5)
                        {
                            XFreqLRef = XFreqLRef + (XFreqHRef - 0.5);
                            XFreqHRef = 0.5;
                        }
                        CreateFilter(FilterWindowRef, XFreqLRef, XFreqHRef);
                        XFreqLRef__ = XFreqLRef * ((double)SpectrumLines) * 2.0;
                        XFreqHRef__ = XFreqHRef * ((double)SpectrumLines) * 2.0;
                    }
                }
                else
                {
                    if (Btn == 1)
                    {
                        if (Diff(Val, max(min(XFreqL, MaxVal), MinVal)) < Diff(Val, max(min(XFreqH, MaxVal), MinVal)))
                        {
                            XFreqL = Val;
                            if (XFreqH < XFreqL) { XFreqH = XFreqL; }
                        }
                        else
                        {
                            XFreqH = Val;
                            if (XFreqH < XFreqL) { XFreqL = XFreqH; }
                        }
                        CreateFilter(FilterWindow, XFreqL, XFreqH);
                        MorseEncoderCore_.CalcPeriod(XFreqL, XFreqH);
                        XFreqL__ = XFreqL * ((double)SpectrumLines) * 2.0;
                        XFreqH__ = XFreqH * ((double)SpectrumLines) * 2.0;
                    }
                    if (Btn == 2)
                    {
                        if (Diff(Val, max(min(XFreqLRef, MaxVal), MinVal)) < Diff(Val, max(min(XFreqHRef, MaxVal), MinVal)))
                        {
                            XFreqLRef = Val;
                            if (XFreqHRef < XFreqLRef) { XFreqHRef = XFreqLRef; }
                        }
                        else
                        {
                            XFreqHRef = Val;
                            if (XFreqHRef < XFreqLRef) { XFreqLRef = XFreqHRef; }
                        }
                        CreateFilter(FilterWindowRef, XFreqLRef, XFreqHRef);
                        XFreqLRef__ = XFreqLRef * ((double)SpectrumLines) * 2.0;
                        XFreqHRef__ = XFreqHRef * ((double)SpectrumLines) * 2.0;
                    }
                }
                MouseMode = 1;
            }

            // Clicked above or below spectrogram - resetting filter
            if (ClickAbove || (ClickBelow && MouseMode == 1))
            {
                if (Btn == 1)
                {
                    XFreqL = 0.0;
                    XFreqH = 0.5;
                    CreateFilter(FilterWindow, XFreqL, XFreqH);
                    MorseEncoderCore_.CalcPeriod(XFreqL, XFreqH);
                    XFreqL__ = XFreqL * ((double)SpectrumLines) * 2.0;
                    XFreqH__ = XFreqH * ((double)SpectrumLines) * 2.0;
                }
                if (Btn == 2)
                {
                    XFreqLRef = 0.0;
                    XFreqHRef = 0.5;
                    CreateFilter(FilterWindowRef, XFreqLRef, XFreqHRef);
                    XFreqLRef__ = XFreqLRef * ((double)SpectrumLines) * 2.0;
                    XFreqHRef__ = XFreqHRef * ((double)SpectrumLines) * 2.0;
                }
            }
        }

        // Clicked on VU bar - discrete signal correcting
        if (ClickBelow)
        {
            if (((MouseMode == 0) || (MouseMode == 2)) && ((SpectrogramDrawVU == 2) || (SpectrogramDrawVU == 3)) && (DecodeCorrection))
            {
                int X1 = min(X, MouseX);
                int X2 = max(X, MouseX);

                if ((SpectrogramDrawMode == 0) || (SpectrogramDrawMode == 1))
                {

                    bool Half = ((SpectrogramDrawMode == 1) && ((MouseLineNumber & 1) == 1));
                    int Buf1 = -1;
                    int Buf2 = -1;

                    if ((SpectrogramDrawMode == 0))
                    {
                        Buf1 = (MouseLineNumber * DecodeBufferW) + X1;
                        Buf2 = (MouseLineNumber * DecodeBufferW) + X2;
                    }
                    if ((SpectrogramDrawMode == 1))
                    {
                        Buf1 = ((MouseLineNumber >> 1) * DecodeBufferW) + X1;
                        Buf2 = ((MouseLineNumber >> 1) * DecodeBufferW) + X2;

                        if (Half)
                        {
                            Buf1 = Buf1 + (DecodeBufferW >> 1);
                            Buf2 = Buf2 + (DecodeBufferW >> 1);
                        }
                    }

                    int T, TX, II, II0, IIX;
                    if ((Buf1 >= 0) && (Buf2 >= 0))
                    {
                        for (II = Buf1; II <= Buf2; II++)
                        {
                            II0 = II % DecodeBufferT;
                            IIX = (II + (DecodeBufferW >> 1)) % DecodeBufferT;

                            if (SpectrogramDrawMode == 1)
                            {
                                T = ((((II0 / DecodeBufferW) + 1) * ((SpectrogramDrawLineWidth << 1))) - 1 - SpectrogramDrawLineWidth);
                                TX = ((((IIX / DecodeBufferW) + 0) * ((SpectrogramDrawLineWidth << 1))) - 1);
                                if (TX < 0)
                                {
                                    TX += ((DecodeBufferL + DecodeBufferL) * SpectrogramDrawLineWidth);
                                }
                            }
                            else
                            {
                                T = ((((II0 / DecodeBufferW) + 1) * (SpectrogramDrawLineWidth)) - 1);
                                TX = T;
                            }

                            T = (T * SpectrogramFullMaxW) + (II0 % DecodeBufferW);
                            TX = (TX * SpectrogramFullMaxW) + (IIX % DecodeBufferW);

                            T = T << 2;
                            TX = TX << 2;

                            for (int I = 0; I < 16; I++)
                            {
                                if (Btn == 1)
                                {
                                    SpectrogramPicture[T + 0] = 0;
                                    SpectrogramPicture[T + 1] = 255;
                                    SpectrogramPicture[T + 2] = 255;
                                    if (SpectrogramDrawMode == 1)
                                    {
                                        SpectrogramPicture[TX + 0] = 0;
                                        SpectrogramPicture[TX + 1] = 255;
                                        SpectrogramPicture[TX + 2] = 255;
                                    }
                                    DecodeBuffer[II0] = b00000100;
                                }
                                if (Btn == 2)
                                {
                                    SpectrogramPicture[T + 0] = 255;
                                    SpectrogramPicture[T + 1] = 0;
                                    SpectrogramPicture[T + 2] = 0;
                                    if (SpectrogramDrawMode == 1)
                                    {
                                        SpectrogramPicture[TX + 0] = 255;
                                        SpectrogramPicture[TX + 1] = 0;
                                        SpectrogramPicture[TX + 2] = 0;
                                    }
                                    DecodeBuffer[II0] = b00000000;
                                }
                                T -= (SpectrogramFullMaxW << 2);
                                TX -= (SpectrogramFullMaxW << 2);
                            }
                        }
                    }
                }
                MouseMode = 2;
            }
        }
    }

    if (Btn == 0)
    {
        MousePressed = false;
        MouseMode = 0;
    }
    MouseX = X;
    MouseY = Y;
}


// Signal decoding procedure
void AppCore::DecodeProcedure(char NextSign)
{
    if (MorseWork)
    {
        if (NextSign >= 0)
        {
            if (DecodeLastSign != NextSign)
            {
                if (DecodeSignLength > 0)
                {
                    if (NextSign)
                    {
                        MorseDecoderCore_.BufferAdd(0 - (DecodeSignLength * 100 * SpectrogramStep));
                    }
                    else
                    {
                        MorseDecoderCore_.BufferAdd((DecodeSignLength * 100 * SpectrogramStep));
                    }
                }
                DecodeSignLength = 1;
                DecodeLastSign = NextSign;
            }
            else
            {
                DecodeSignLength++;
                if (DecodeSignLength == (MorseDecoderCore_.PauseLongThresholdX / SpectrogramStep))
                {
                    MorseDecoderCore_.BufferAdd(0);
                }
            }
        }
    }
    else
    {
        DecodeSignLength = 0;
        DecodeLastSign = 0;
    }
}

void AppCore::BufPrev(int X)
{
    X = X * BufSampleRate;
    if (AudioFileBufferSession)
    {
        int WorkX = BufOffset;
        if ((X > 0) && (X < WorkX))
        {
            WorkX = X;
        }
        BufOffset -= WorkX;
    }
    else
    {
        if (ReplayBufferL > 0)
        {
            if (X > 0)
            {
                BufOffset += X;
                if (BufOffset > ReplayBufferF)
                {
                    BufOffset = ReplayBufferF;
                }
            }
            else
            {
                BufOffset = ReplayBufferF;
            }
        }
        else
        {
            BufOffset = 0;
        }
    }
}

void AppCore::BufNext(int X)
{
    X = X * BufSampleRate;
    if (AudioFileBufferSession)
    {
        int WorkX = BufSize - BufOffset;
        if ((X > 0) && (X < WorkX))
        {
            WorkX = X;
        }
        BufOffset += WorkX;
    }
    else
    {
        if (ReplayBufferL > 0)
        {
            if (X > 0)
            {
                BufOffset -= X;
                if (BufOffset < 0)
                {
                    BufOffset = 0;
                }
            }
            else
            {
                BufOffset = 0;
            }
        }
        else
        {
            BufOffset = 0;
        }
    }
}

QString AppCore::MorseBufGet()
{
    QString X = *MorseBuf;
    MorseBuf->clear();
    return X;
}

void AppCore::GetPlaybackSamples(short *Smp, int ChunkSize)
{
    //cout << "P " << ChunkSize << endl;
    for (int I = 0; I < ChunkSize; I++)
    {
        Smp[I] = 0;
    }

    if (Settings_->PlaybackMode == 0)
    {
        return;
    }

    //cout << AudioPlaybackBuf.Count << endl;
    while (AudioPlaybackBuf.Count > Settings_->PlaybackBufSizeMax)
    {
        AudioPlaybackBuf.Get(ChunkSize);
    }
    if (AudioPlaybackBuf.Count > Settings_->PlaybackBufSizeMin)
    {
        AudioPlaybackBuf.First(Smp, ChunkSize);

        // No compensation
        if (Settings_->PlaybackBufCompensation == 0)
        {
            AudioPlaybackBuf.Get(ChunkSize);
        }

        // Playing faster than recording - adding one sample
        if (Settings_->PlaybackBufCompensation > 0)
        {
            if (PlaybackCompensationCounter > 0)
            {
                PlaybackCompensationCounter--;
                AudioPlaybackBuf.Get(ChunkSize);
            }
            else
            {
                PlaybackCompensationCounter = Settings_->PlaybackBufCompensation;
                AudioPlaybackBuf.Get(ChunkSize - 1);
            }
        }

        // Playing slower than recording - omitting one sample
        if (Settings_->PlaybackBufCompensation < 0)
        {
            if (PlaybackCompensationCounter > 0)
            {
                PlaybackCompensationCounter--;
                AudioPlaybackBuf.Get(ChunkSize);
            }
            else
            {
                PlaybackCompensationCounter = Settings_->PlaybackBufCompensation;
                AudioPlaybackBuf.Get(ChunkSize + 1);
            }
        }
    }
}

void AppCore::ClearBuffers()
{
    for (int I = 0; I < SpectrumArraySize; I++)
    {
        SpectrumBufRaw_R[I] = 0;
        SpectrumBufRaw_G[I] = 0;
        SpectrumBufRaw_B[I] = 0;
        SpectrumBufFil_R[I] = 0;
        SpectrumBufFil_G[I] = 0;
        SpectrumBufFil_B[I] = 0;
        SpectrumBufRef_R[I] = 0;
        SpectrumBufRef_G[I] = 0;
        SpectrumBufRef_B[I] = 0;
    }
    WholeRepaint = 1;
}
