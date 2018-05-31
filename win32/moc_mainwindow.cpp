/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MorseCode/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[90];
    char stringdata0[2318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_SoundStart_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "on_SoundStop_clicked"
QT_MOC_LITERAL(4, 55, 14), // "AudioTimerTick"
QT_MOC_LITERAL(5, 70, 9), // "GuiChange"
QT_MOC_LITERAL(6, 80, 31), // "on_SpectrogramAmpT_valueChanged"
QT_MOC_LITERAL(7, 112, 5), // "value"
QT_MOC_LITERAL(8, 118, 38), // "on_SpectrogramResolutionT_val..."
QT_MOC_LITERAL(9, 157, 32), // "on_SpectrogramZoomT_valueChanged"
QT_MOC_LITERAL(10, 190, 22), // "on_VUAmpT_valueChanged"
QT_MOC_LITERAL(11, 213, 23), // "on_VUSizeT_valueChanged"
QT_MOC_LITERAL(12, 237, 30), // "on_CalcThrAttackT_valueChanged"
QT_MOC_LITERAL(13, 268, 29), // "on_CalcThrDecayT_valueChanged"
QT_MOC_LITERAL(14, 298, 35), // "on_ProcessCountAttackT_valueC..."
QT_MOC_LITERAL(15, 334, 34), // "on_ProcessCountDecayT_valueCh..."
QT_MOC_LITERAL(16, 369, 19), // "on_WithRefC_toggled"
QT_MOC_LITERAL(17, 389, 7), // "checked"
QT_MOC_LITERAL(18, 397, 32), // "on_SpectrogramStepT_valueChanged"
QT_MOC_LITERAL(19, 430, 24), // "on_SoundSettings_clicked"
QT_MOC_LITERAL(20, 455, 25), // "on_SpectrogramL_MouseMove"
QT_MOC_LITERAL(21, 481, 3), // "Btn"
QT_MOC_LITERAL(22, 485, 1), // "X"
QT_MOC_LITERAL(23, 487, 1), // "Y"
QT_MOC_LITERAL(24, 489, 26), // "on_SpectrogramL_MousePress"
QT_MOC_LITERAL(25, 516, 28), // "on_SpectrogramL_MouseRelease"
QT_MOC_LITERAL(26, 545, 20), // "on_PrintText_clicked"
QT_MOC_LITERAL(27, 566, 21), // "on_MorseCalcB_clicked"
QT_MOC_LITERAL(28, 588, 27), // "on_MorseBufferClear_clicked"
QT_MOC_LITERAL(29, 616, 27), // "on_MorseBufferBegin_clicked"
QT_MOC_LITERAL(30, 644, 25), // "on_MorseSettingsB_clicked"
QT_MOC_LITERAL(31, 670, 24), // "on_MorseRealTime_toggled"
QT_MOC_LITERAL(32, 695, 29), // "on_MorseBufferCurrent_clicked"
QT_MOC_LITERAL(33, 725, 25), // "on_BufSpeedS_valueChanged"
QT_MOC_LITERAL(34, 751, 18), // "on_BufPrev_clicked"
QT_MOC_LITERAL(35, 770, 22), // "on_BufPrevLong_clicked"
QT_MOC_LITERAL(36, 793, 23), // "on_BufPrevShort_clicked"
QT_MOC_LITERAL(37, 817, 18), // "on_BufNext_clicked"
QT_MOC_LITERAL(38, 836, 22), // "on_BufNextLong_clicked"
QT_MOC_LITERAL(39, 859, 23), // "on_BufNextShort_clicked"
QT_MOC_LITERAL(40, 883, 18), // "on_BufPlay_clicked"
QT_MOC_LITERAL(41, 902, 19), // "on_BufPause_clicked"
QT_MOC_LITERAL(42, 922, 20), // "on_MorseWork_toggled"
QT_MOC_LITERAL(43, 943, 26), // "on_MorseBufferLast_clicked"
QT_MOC_LITERAL(44, 970, 20), // "on_InputText_clicked"
QT_MOC_LITERAL(45, 991, 28), // "on_SoundSpectrumFull_clicked"
QT_MOC_LITERAL(46, 1020, 30), // "on_SpectrogramSettings_clicked"
QT_MOC_LITERAL(47, 1051, 32), // "on_SpectrogramBaseT_valueChanged"
QT_MOC_LITERAL(48, 1084, 34), // "on_SpectrogramOffsetT_valueCh..."
QT_MOC_LITERAL(49, 1119, 34), // "on_SpectrogramWindowT_valueCh..."
QT_MOC_LITERAL(50, 1154, 24), // "on_BufSpeed1L_MousePress"
QT_MOC_LITERAL(51, 1179, 1), // "B"
QT_MOC_LITERAL(52, 1181, 24), // "on_BufSpeed2L_MousePress"
QT_MOC_LITERAL(53, 1206, 29), // "on_SpectrogramAmpL_MousePress"
QT_MOC_LITERAL(54, 1236, 29), // "on_SpectrogramAmpV_MousePress"
QT_MOC_LITERAL(55, 1266, 36), // "on_SpectrogramResolutionL_Mou..."
QT_MOC_LITERAL(56, 1303, 36), // "on_SpectrogramResolutionV_Mou..."
QT_MOC_LITERAL(57, 1340, 32), // "on_SpectrogramWindowL_MousePress"
QT_MOC_LITERAL(58, 1373, 32), // "on_SpectrogramWindowV_MousePress"
QT_MOC_LITERAL(59, 1406, 30), // "on_SpectrogramZoomL_MousePress"
QT_MOC_LITERAL(60, 1437, 30), // "on_SpectrogramZoomV_MousePress"
QT_MOC_LITERAL(61, 1468, 32), // "on_SpectrogramOffsetL_MousePress"
QT_MOC_LITERAL(62, 1501, 32), // "on_SpectrogramOffsetV_MousePress"
QT_MOC_LITERAL(63, 1534, 30), // "on_SpectrogramStepL_MousePress"
QT_MOC_LITERAL(64, 1565, 30), // "on_SpectrogramStepV_MousePress"
QT_MOC_LITERAL(65, 1596, 30), // "on_SpectrogramBaseL_MousePress"
QT_MOC_LITERAL(66, 1627, 30), // "on_SpectrogramBaseV_MousePress"
QT_MOC_LITERAL(67, 1658, 20), // "on_VUAmpL_MousePress"
QT_MOC_LITERAL(68, 1679, 20), // "on_VUAmpV_MousePress"
QT_MOC_LITERAL(69, 1700, 21), // "on_VUSizeL_MousePress"
QT_MOC_LITERAL(70, 1722, 21), // "on_VUSizeV_MousePress"
QT_MOC_LITERAL(71, 1744, 28), // "on_CalcThrAttackL_MousePress"
QT_MOC_LITERAL(72, 1773, 28), // "on_CalcThrAttackV_MousePress"
QT_MOC_LITERAL(73, 1802, 27), // "on_CalcThrDecayL_MousePress"
QT_MOC_LITERAL(74, 1830, 27), // "on_CalcThrDecayV_MousePress"
QT_MOC_LITERAL(75, 1858, 33), // "on_ProcessCountAttackL_MouseP..."
QT_MOC_LITERAL(76, 1892, 33), // "on_ProcessCountAttackV_MouseP..."
QT_MOC_LITERAL(77, 1926, 32), // "on_ProcessCountDecayL_MousePress"
QT_MOC_LITERAL(78, 1959, 32), // "on_ProcessCountDecayV_MousePress"
QT_MOC_LITERAL(79, 1992, 31), // "on_SpectrogramLinesL_MousePress"
QT_MOC_LITERAL(80, 2024, 31), // "on_SpectrogramLinesV_MousePress"
QT_MOC_LITERAL(81, 2056, 32), // "on_SpectrogramMinMaxL_MousePress"
QT_MOC_LITERAL(82, 2089, 32), // "on_SpectrogramMinMaxV_MousePress"
QT_MOC_LITERAL(83, 2122, 33), // "on_SpectrogramLinesT_valueCha..."
QT_MOC_LITERAL(84, 2156, 31), // "on_DrawMode_currentIndexChanged"
QT_MOC_LITERAL(85, 2188, 5), // "index"
QT_MOC_LITERAL(86, 2194, 29), // "on_DrawVU_currentIndexChanged"
QT_MOC_LITERAL(87, 2224, 29), // "on_VUMode_currentIndexChanged"
QT_MOC_LITERAL(88, 2254, 28), // "on_DecodeCorrectionC_toggled"
QT_MOC_LITERAL(89, 2283, 34) // "on_SpectrogramMinMaxT_valueCh..."

    },
    "MainWindow\0on_SoundStart_clicked\0\0"
    "on_SoundStop_clicked\0AudioTimerTick\0"
    "GuiChange\0on_SpectrogramAmpT_valueChanged\0"
    "value\0on_SpectrogramResolutionT_valueChanged\0"
    "on_SpectrogramZoomT_valueChanged\0"
    "on_VUAmpT_valueChanged\0on_VUSizeT_valueChanged\0"
    "on_CalcThrAttackT_valueChanged\0"
    "on_CalcThrDecayT_valueChanged\0"
    "on_ProcessCountAttackT_valueChanged\0"
    "on_ProcessCountDecayT_valueChanged\0"
    "on_WithRefC_toggled\0checked\0"
    "on_SpectrogramStepT_valueChanged\0"
    "on_SoundSettings_clicked\0"
    "on_SpectrogramL_MouseMove\0Btn\0X\0Y\0"
    "on_SpectrogramL_MousePress\0"
    "on_SpectrogramL_MouseRelease\0"
    "on_PrintText_clicked\0on_MorseCalcB_clicked\0"
    "on_MorseBufferClear_clicked\0"
    "on_MorseBufferBegin_clicked\0"
    "on_MorseSettingsB_clicked\0"
    "on_MorseRealTime_toggled\0"
    "on_MorseBufferCurrent_clicked\0"
    "on_BufSpeedS_valueChanged\0on_BufPrev_clicked\0"
    "on_BufPrevLong_clicked\0on_BufPrevShort_clicked\0"
    "on_BufNext_clicked\0on_BufNextLong_clicked\0"
    "on_BufNextShort_clicked\0on_BufPlay_clicked\0"
    "on_BufPause_clicked\0on_MorseWork_toggled\0"
    "on_MorseBufferLast_clicked\0"
    "on_InputText_clicked\0on_SoundSpectrumFull_clicked\0"
    "on_SpectrogramSettings_clicked\0"
    "on_SpectrogramBaseT_valueChanged\0"
    "on_SpectrogramOffsetT_valueChanged\0"
    "on_SpectrogramWindowT_valueChanged\0"
    "on_BufSpeed1L_MousePress\0B\0"
    "on_BufSpeed2L_MousePress\0"
    "on_SpectrogramAmpL_MousePress\0"
    "on_SpectrogramAmpV_MousePress\0"
    "on_SpectrogramResolutionL_MousePress\0"
    "on_SpectrogramResolutionV_MousePress\0"
    "on_SpectrogramWindowL_MousePress\0"
    "on_SpectrogramWindowV_MousePress\0"
    "on_SpectrogramZoomL_MousePress\0"
    "on_SpectrogramZoomV_MousePress\0"
    "on_SpectrogramOffsetL_MousePress\0"
    "on_SpectrogramOffsetV_MousePress\0"
    "on_SpectrogramStepL_MousePress\0"
    "on_SpectrogramStepV_MousePress\0"
    "on_SpectrogramBaseL_MousePress\0"
    "on_SpectrogramBaseV_MousePress\0"
    "on_VUAmpL_MousePress\0on_VUAmpV_MousePress\0"
    "on_VUSizeL_MousePress\0on_VUSizeV_MousePress\0"
    "on_CalcThrAttackL_MousePress\0"
    "on_CalcThrAttackV_MousePress\0"
    "on_CalcThrDecayL_MousePress\0"
    "on_CalcThrDecayV_MousePress\0"
    "on_ProcessCountAttackL_MousePress\0"
    "on_ProcessCountAttackV_MousePress\0"
    "on_ProcessCountDecayL_MousePress\0"
    "on_ProcessCountDecayV_MousePress\0"
    "on_SpectrogramLinesL_MousePress\0"
    "on_SpectrogramLinesV_MousePress\0"
    "on_SpectrogramMinMaxL_MousePress\0"
    "on_SpectrogramMinMaxV_MousePress\0"
    "on_SpectrogramLinesT_valueChanged\0"
    "on_DrawMode_currentIndexChanged\0index\0"
    "on_DrawVU_currentIndexChanged\0"
    "on_VUMode_currentIndexChanged\0"
    "on_DecodeCorrectionC_toggled\0"
    "on_SpectrogramMinMaxT_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      81,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  419,    2, 0x08 /* Private */,
       3,    0,  420,    2, 0x08 /* Private */,
       4,    0,  421,    2, 0x08 /* Private */,
       5,    0,  422,    2, 0x08 /* Private */,
       6,    1,  423,    2, 0x08 /* Private */,
       8,    1,  426,    2, 0x08 /* Private */,
       9,    1,  429,    2, 0x08 /* Private */,
      10,    1,  432,    2, 0x08 /* Private */,
      11,    1,  435,    2, 0x08 /* Private */,
      12,    1,  438,    2, 0x08 /* Private */,
      13,    1,  441,    2, 0x08 /* Private */,
      14,    1,  444,    2, 0x08 /* Private */,
      15,    1,  447,    2, 0x08 /* Private */,
      16,    1,  450,    2, 0x08 /* Private */,
      18,    1,  453,    2, 0x08 /* Private */,
      19,    0,  456,    2, 0x08 /* Private */,
      20,    3,  457,    2, 0x08 /* Private */,
      24,    3,  464,    2, 0x08 /* Private */,
      25,    3,  471,    2, 0x08 /* Private */,
      26,    0,  478,    2, 0x08 /* Private */,
      27,    0,  479,    2, 0x08 /* Private */,
      28,    0,  480,    2, 0x08 /* Private */,
      29,    0,  481,    2, 0x08 /* Private */,
      30,    0,  482,    2, 0x08 /* Private */,
      31,    1,  483,    2, 0x08 /* Private */,
      32,    0,  486,    2, 0x08 /* Private */,
      33,    1,  487,    2, 0x08 /* Private */,
      34,    0,  490,    2, 0x08 /* Private */,
      35,    0,  491,    2, 0x08 /* Private */,
      36,    0,  492,    2, 0x08 /* Private */,
      37,    0,  493,    2, 0x08 /* Private */,
      38,    0,  494,    2, 0x08 /* Private */,
      39,    0,  495,    2, 0x08 /* Private */,
      40,    0,  496,    2, 0x08 /* Private */,
      41,    0,  497,    2, 0x08 /* Private */,
      42,    1,  498,    2, 0x08 /* Private */,
      43,    0,  501,    2, 0x08 /* Private */,
      44,    0,  502,    2, 0x08 /* Private */,
      45,    0,  503,    2, 0x08 /* Private */,
      46,    0,  504,    2, 0x08 /* Private */,
      47,    1,  505,    2, 0x08 /* Private */,
      48,    1,  508,    2, 0x08 /* Private */,
      49,    1,  511,    2, 0x08 /* Private */,
      50,    3,  514,    2, 0x08 /* Private */,
      52,    3,  521,    2, 0x08 /* Private */,
      53,    3,  528,    2, 0x08 /* Private */,
      54,    3,  535,    2, 0x08 /* Private */,
      55,    3,  542,    2, 0x08 /* Private */,
      56,    3,  549,    2, 0x08 /* Private */,
      57,    3,  556,    2, 0x08 /* Private */,
      58,    3,  563,    2, 0x08 /* Private */,
      59,    3,  570,    2, 0x08 /* Private */,
      60,    3,  577,    2, 0x08 /* Private */,
      61,    3,  584,    2, 0x08 /* Private */,
      62,    3,  591,    2, 0x08 /* Private */,
      63,    3,  598,    2, 0x08 /* Private */,
      64,    3,  605,    2, 0x08 /* Private */,
      65,    3,  612,    2, 0x08 /* Private */,
      66,    3,  619,    2, 0x08 /* Private */,
      67,    3,  626,    2, 0x08 /* Private */,
      68,    3,  633,    2, 0x08 /* Private */,
      69,    3,  640,    2, 0x08 /* Private */,
      70,    3,  647,    2, 0x08 /* Private */,
      71,    3,  654,    2, 0x08 /* Private */,
      72,    3,  661,    2, 0x08 /* Private */,
      73,    3,  668,    2, 0x08 /* Private */,
      74,    3,  675,    2, 0x08 /* Private */,
      75,    3,  682,    2, 0x08 /* Private */,
      76,    3,  689,    2, 0x08 /* Private */,
      77,    3,  696,    2, 0x08 /* Private */,
      78,    3,  703,    2, 0x08 /* Private */,
      79,    3,  710,    2, 0x08 /* Private */,
      80,    3,  717,    2, 0x08 /* Private */,
      81,    3,  724,    2, 0x08 /* Private */,
      82,    3,  731,    2, 0x08 /* Private */,
      83,    1,  738,    2, 0x08 /* Private */,
      84,    1,  741,    2, 0x08 /* Private */,
      86,    1,  744,    2, 0x08 /* Private */,
      87,    1,  747,    2, 0x08 /* Private */,
      88,    1,  750,    2, 0x08 /* Private */,
      89,    1,  753,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   51,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,   85,
    QMetaType::Void, QMetaType::Int,   85,
    QMetaType::Void, QMetaType::Int,   85,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_SoundStart_clicked(); break;
        case 1: _t->on_SoundStop_clicked(); break;
        case 2: _t->AudioTimerTick(); break;
        case 3: _t->GuiChange(); break;
        case 4: _t->on_SpectrogramAmpT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_SpectrogramResolutionT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_SpectrogramZoomT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_VUAmpT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_VUSizeT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_CalcThrAttackT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_CalcThrDecayT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_ProcessCountAttackT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_ProcessCountDecayT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_WithRefC_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_SpectrogramStepT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_SoundSettings_clicked(); break;
        case 16: _t->on_SpectrogramL_MouseMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->on_SpectrogramL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->on_SpectrogramL_MouseRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 19: _t->on_PrintText_clicked(); break;
        case 20: _t->on_MorseCalcB_clicked(); break;
        case 21: _t->on_MorseBufferClear_clicked(); break;
        case 22: _t->on_MorseBufferBegin_clicked(); break;
        case 23: _t->on_MorseSettingsB_clicked(); break;
        case 24: _t->on_MorseRealTime_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_MorseBufferCurrent_clicked(); break;
        case 26: _t->on_BufSpeedS_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_BufPrev_clicked(); break;
        case 28: _t->on_BufPrevLong_clicked(); break;
        case 29: _t->on_BufPrevShort_clicked(); break;
        case 30: _t->on_BufNext_clicked(); break;
        case 31: _t->on_BufNextLong_clicked(); break;
        case 32: _t->on_BufNextShort_clicked(); break;
        case 33: _t->on_BufPlay_clicked(); break;
        case 34: _t->on_BufPause_clicked(); break;
        case 35: _t->on_MorseWork_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->on_MorseBufferLast_clicked(); break;
        case 37: _t->on_InputText_clicked(); break;
        case 38: _t->on_SoundSpectrumFull_clicked(); break;
        case 39: _t->on_SpectrogramSettings_clicked(); break;
        case 40: _t->on_SpectrogramBaseT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_SpectrogramOffsetT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_SpectrogramWindowT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->on_BufSpeed1L_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 44: _t->on_BufSpeed2L_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 45: _t->on_SpectrogramAmpL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 46: _t->on_SpectrogramAmpV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 47: _t->on_SpectrogramResolutionL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 48: _t->on_SpectrogramResolutionV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 49: _t->on_SpectrogramWindowL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 50: _t->on_SpectrogramWindowV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 51: _t->on_SpectrogramZoomL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 52: _t->on_SpectrogramZoomV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 53: _t->on_SpectrogramOffsetL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 54: _t->on_SpectrogramOffsetV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 55: _t->on_SpectrogramStepL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 56: _t->on_SpectrogramStepV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 57: _t->on_SpectrogramBaseL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 58: _t->on_SpectrogramBaseV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 59: _t->on_VUAmpL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 60: _t->on_VUAmpV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 61: _t->on_VUSizeL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 62: _t->on_VUSizeV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 63: _t->on_CalcThrAttackL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 64: _t->on_CalcThrAttackV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 65: _t->on_CalcThrDecayL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 66: _t->on_CalcThrDecayV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 67: _t->on_ProcessCountAttackL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 68: _t->on_ProcessCountAttackV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 69: _t->on_ProcessCountDecayL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 70: _t->on_ProcessCountDecayV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 71: _t->on_SpectrogramLinesL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 72: _t->on_SpectrogramLinesV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 73: _t->on_SpectrogramMinMaxL_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 74: _t->on_SpectrogramMinMaxV_MousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 75: _t->on_SpectrogramLinesT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->on_DrawMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->on_DrawVU_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->on_VUMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->on_DecodeCorrectionC_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 80: _t->on_SpectrogramMinMaxT_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 81)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 81;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 81)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 81;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
