/*
 * LIBEMBROIDERY HEADER
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Note that all new defines start with "EMB_", all functions with "emb" and all
 * typedefs with "Emb" to protect against namespace pollution. (INCOMPLETE)
 */

#ifndef EMB_LIBRARY_HEADER__
#define EMB_LIBRARY_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/* This setting overrides large tables so they aren't included in embedded
 * systems.
 */
#ifndef EMB_EMBEDDED_VERSION
#define EMB_EMBEDDED_VERSION          0
#endif

/* MACROS
 *****************************************************************************
 *
 * Machine codes for stitch flags.
 * These all represent distinct bits as some of them can be combined on some
 * machines.
 *
 * Missing change color?
 *
 * Stitch to (x, y). */
#define NORMAL                      0x00
/* Move to (x, y). */
#define JUMP                        0x01
/* Trim and move to (x, y). */
#define TRIM                        0x02
/* Pause machine for a thread change. */
#define STOP                        0x04
/* Add a sequin at the current co-ordinates. */
#define SEQUIN                      0x08
/* end of program */
#define END                         0x10

/* Format identifiers */
#define EMB_FORMAT_100           0
#define EMB_FORMAT_10O           1
#define EMB_FORMAT_ART           2
#define EMB_FORMAT_BMC           3
#define EMB_FORMAT_BRO           4
#define EMB_FORMAT_CND           5
#define EMB_FORMAT_COL           6
#define EMB_FORMAT_CSD           7
#define EMB_FORMAT_CSV           8
#define EMB_FORMAT_DAT           9
#define EMB_FORMAT_DEM          10
#define EMB_FORMAT_DSB          11
#define EMB_FORMAT_DST          12
#define EMB_FORMAT_DSZ          13
#define EMB_FORMAT_DXF          14
#define EMB_FORMAT_EDR          15
#define EMB_FORMAT_EMD          16
#define EMB_FORMAT_EXP          17
#define EMB_FORMAT_EXY          18
#define EMB_FORMAT_EYS          19
#define EMB_FORMAT_FXY          20
#define EMB_FORMAT_GC           21
#define EMB_FORMAT_GNC          22
#define EMB_FORMAT_GT           23
#define EMB_FORMAT_HUS          24
#define EMB_FORMAT_INB          25
#define EMB_FORMAT_INF          26
#define EMB_FORMAT_JEF          27
#define EMB_FORMAT_KSM          28
#define EMB_FORMAT_MAX          29
#define EMB_FORMAT_MIT          30
#define EMB_FORMAT_NEW          31
#define EMB_FORMAT_OFM          32
#define EMB_FORMAT_PCD          33
#define EMB_FORMAT_PCM          34
#define EMB_FORMAT_PCQ          35
#define EMB_FORMAT_PCS          36
#define EMB_FORMAT_PEC          37
#define EMB_FORMAT_PEL          38
#define EMB_FORMAT_PEM          39
#define EMB_FORMAT_PES          40
#define EMB_FORMAT_PHB          41
#define EMB_FORMAT_PHC          42
#define EMB_FORMAT_PLT          43
#define EMB_FORMAT_RGB          44
#define EMB_FORMAT_SEW          45
#define EMB_FORMAT_SHV          46
#define EMB_FORMAT_SST          47
#define EMB_FORMAT_STX          48
#define EMB_FORMAT_SVG          49
#define EMB_FORMAT_T01          50
#define EMB_FORMAT_T09          51
#define EMB_FORMAT_TAP          52
#define EMB_FORMAT_THR          53
#define EMB_FORMAT_TXT          54
#define EMB_FORMAT_U00          55
#define EMB_FORMAT_U01          56
#define EMB_FORMAT_VIP          57
#define EMB_FORMAT_VP3          58
#define EMB_FORMAT_XXX          59
#define EMB_FORMAT_ZSK          60

/* Thread color */
#define Arc_Polyester           0
#define Arc_Rayon               1
#define CoatsAndClark_Rayon     2
#define Exquisite_Polyester     3
#define Fufu_Polyester          4
#define Fufu_Rayon              5
#define Hemingworth_Polyester   6
#define Isacord_Polyester       7
#define Isafil_Rayon            8
#define Marathon_Polyester      9
#define Marathon_Rayon          10
#define Madeira_Polyester       11
#define Madeira_Rayon           12
#define Metro_Polyester         13
#define Pantone                 14
#define RobisonAnton_Polyester  15
#define RobisonAnton_Rayon      16
#define Sigma_Polyester         17
#define Sulky_Rayon             18
#define ThreadArt_Rayon         19
#define ThreadArt_Polyester     20
#define ThreaDelight_Polyester  21
#define Z102_Isacord_Polyester  22
#define SVG_Colors              23
#define hus_thread              24
#define jef_thread              25
#define pcm_thread              26
#define pec_thread              27
#define shv_thread              28
#define dxf_color               29

/* EmbGeometry types, should include all of the possible rendering types
 * for EmbroiderModder and internal types for stitch processing (like
 * fills).
 */
#define EMB_ARRAY               0
#define EMB_ARC                 1
#define EMB_CIRCLE              2
#define EMB_DIM_DIAMETER        3
#define EMB_DIM_LEADER          4
#define EMB_ELLIPSE             5
#define EMB_FLAG                6
#define EMB_LINE                7
#define EMB_IMAGE               8
#define EMB_PATH                9
#define EMB_POINT               10
#define EMB_POLYGON             11
#define EMB_POLYLINE            12
#define EMB_RECT                13
#define EMB_SPLINE              14
#define EMB_STITCH              15
#define EMB_TEXT_SINGLE         16
#define EMB_TEXT_MULTI          17
#define EMB_VECTOR              18
#define EMB_THREAD              19

#define EMBFORMAT_UNSUPPORTED                   0
#define EMBFORMAT_STITCHONLY                    1
#define EMBFORMAT_OBJECTONLY                    2
#define EMBFORMAT_STCHANDOBJ                    3 /* binary operation: 1+2=3 */

#define numberOfFormats                        61

#define CHUNK_SIZE                            128

#define EMB_MAX_LAYERS                         10
#define MAX_THREADS                           256
#define EMBFORMAT_MAXEXT                        3
/* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC                      50
/* the longest possible description string length */
#define MAX_STITCHES                      1000000

/* Libembroidery's handling of integer types.
 */
#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

/* Most machines are little endian (including the developer's), so default to
 * that.
 */
#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

#define EMB_INT16_BIG                           2
#define EMB_INT16_LITTLE                        3
#define EMB_INT32_BIG                           4
#define EMB_INT32_LITTLE                        5

/* Identifiers for different PES versions. */
#define PES0001         0
#define PES0020         1
#define PES0022         2
#define PES0030         3
#define PES0040         4
#define PES0050         5
#define PES0055         6
#define PES0056         7
#define PES0060         8
#define PES0070         9
#define PES0080        10
#define PES0090        11
#define PES0100        12
#define N_PES_VERSIONS 13


/**
 * Type of sector
 * Compound File Sector (CFS)
 */
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector   0xFFFFFFFD
#define CompoundFileSector_EndOfChain   0xFFFFFFFE
#define CompoundFileSector_FreeSector   0xFFFFFFFF

/**
 * Type of directory object
 */
#define ObjectTypeUnknown   0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage   0x01 /*!< a directory type object */
#define ObjectTypeStream    0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
 * Special values for Stream Identifiers
 */
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream           0xFFFFFFFF /*!< There is no valid stream Id            */

#define ELEMENT_XML              0
#define ELEMENT_A                1
#define ELEMENT_ANIMATE          2
#define ELEMENT_ANIMATECOLOR     3
#define ELEMENT_ANIMATEMOTION    4
#define ELEMENT_ANIMATETRANSFORM 5
#define ELEMENT_ANIMATION        6
#define ELEMENT_AUDIO            7
#define ELEMENT_CIRCLE           8
#define ELEMENT_DEFS             9
#define ELEMENT_DESC            10
#define ELEMENT_DISCARD         11
#define ELEMENT_ELLIPSE         12
#define ELEMENT_FONT            13
#define ELEMENT_FONT_FACE       14
#define ELEMENT_FONT_FACE_SRC   15
#define ELEMENT_FONT_FACE_URI   16
#define ELEMENT_FOREIGN_OBJECT  17
#define ELEMENT_G               18
#define ELEMENT_GLYPH           19
#define ELEMENT_HANDLER         20
#define ELEMENT_HKERN           21
#define ELEMENT_IMAGE           22
#define ELEMENT_LINE            23
#define ELEMENT_LINEAR_GRADIENT 24
#define ELEMENT_LISTENER        25
#define ELEMENT_METADATA        26
#define ELEMENT_MISSING_GLYPH   27
#define ELEMENT_MPATH           28
#define ELEMENT_PATH            29
#define ELEMENT_POLYGON         30
#define ELEMENT_POLYLINE        31
#define ELEMENT_PREFETCH        32
#define ELEMENT_RADIAL_GRADIENT 33
#define ELEMENT_RECT            34
#define ELEMENT_SCRIPT          35
#define ELEMENT_SET             36
#define ELEMENT_SOLID_COLOR     37
#define ELEMENT_STOP            38
#define ELEMENT_SVG             39
#define ELEMENT_SWITCH          40
#define ELEMENT_TBREAK          41
#define ELEMENT_TEXT            42
#define ELEMENT_TEXT_AREA       43
#define ELEMENT_TITLE           44
#define ELEMENT_TSPAN           45
#define ELEMENT_USE             46
#define ELEMENT_VIDEO           47

/* INTERNAL DEFINES */
#define RED_TERM_COLOR      "\x1B[0;31m"
#define GREEN_TERM_COLOR    "\x1B[0;32m"
#define YELLOW_TERM_COLOR   "\x1B[1;33m"
#define RESET_TERM_COLOR       "\033[0m"

#define HOOP_126X110                  0
#define HOOP_110X110                  1
#define HOOP_50X50                    2
#define HOOP_140X200                  3
#define HOOP_230X200                  4


/* DXF Version Identifiers */
#define DXF_VERSION_R10 "AC1006"
#define DXF_VERSION_R11 "AC1009"
#define DXF_VERSION_R12 "AC1009"
#define DXF_VERSION_R13 "AC1012"
#define DXF_VERSION_R14 "AC1014"
#define DXF_VERSION_R15 "AC1015"
#define DXF_VERSION_R18 "AC1018"
#define DXF_VERSION_R21 "AC1021"
#define DXF_VERSION_R24 "AC1024"
#define DXF_VERSION_R27 "AC1027"

#define DXF_VERSION_2000 "AC1015"
#define DXF_VERSION_2002 "AC1015"
#define DXF_VERSION_2004 "AC1018"
#define DXF_VERSION_2006 "AC1018"
#define DXF_VERSION_2007 "AC1021"
#define DXF_VERSION_2009 "AC1021"
#define DXF_VERSION_2010 "AC1024"
#define DXF_VERSION_2013 "AC1027"

#define SVG_CREATOR_NULL              0
#define SVG_CREATOR_EMBROIDERMODDER   1
#define SVG_CREATOR_ILLUSTRATOR       2
#define SVG_CREATOR_INKSCAPE          3

#define SVG_EXPECT_NULL               0
#define SVG_EXPECT_ELEMENT            1
#define SVG_EXPECT_ATTRIBUTE          2
#define SVG_EXPECT_VALUE              3

/*  SVG_TYPES
 *  ---------
 */
#define SVG_NULL                      0
#define SVG_ELEMENT                   1
#define SVG_PROPERTY                  2
#define SVG_MEDIA_PROPERTY            3
#define SVG_ATTRIBUTE                 4
#define SVG_CATCH_ALL                 5

/* path flag codes */
#define LINETO             0
#define MOVETO             1
#define BULGETOCONTROL     2
#define BULGETOEND         4
#define ELLIPSETORAD       8
#define ELLIPSETOEND      16
#define CUBICTOCONTROL1   32
#define CUBICTOCONTROL2   64
#define CUBICTOEND       128
#define QUADTOCONTROL    256
#define QUADTOEND        512

/* Utility macros
 */
#define EMB_MIN(A, B) (((A) < (B)) ? (A) : (B))
#define EMB_MAX(A, B) (((A) > (B)) ? (A) : (B))

#if defined(_WIN32) && !defined(WIN32)
#define WIN32
#endif

/* When building a shared library,
* use the proper export keyword depending on the compiler */
#define EMB_PUBLIC
#if defined(LIBEMBROIDERY_SHARED)
    #undef EMB_PUBLIC
    #if defined(__WIN32__) || defined(WIN32)
        #define EMB_PUBLIC __declspec(dllexport)
    #else
        #define EMB_PUBLIC __attribute__ ((visibility("default")))
    #endif
#endif

/* TYPEDEFS AND STRUCTS
 *******************************************************************/

/* Should some platform need a different precision, this is typedef-ed
 * and used in place of all real types where possible.
 */
typedef float EmbReal;

/* EmbColor uses the light primaries: red, green, blue in that order. */
typedef struct EmbColor_
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} EmbColor;

/* The basic type to represent points absolutely or represent directions.
 *
 * Positive y is up, units are in mm.
 */
typedef struct EmbVector_
{
    EmbReal x;
    EmbReal y;
} EmbVector;

/* . */
typedef struct EmbTime_
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} EmbTime;

/* The basic array type. */
typedef struct EmbArray_ EmbArray;

/* double-indirection file allocation table references */
typedef struct _bcf_file_difat
{
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;
} bcf_file_difat;

/* . */
typedef struct _bcf_file_fat
{
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;
} bcf_file_fat;

/* . */
typedef struct _bcf_directory_entry
{
    char                         directoryEntryName[32];
    unsigned short               directoryEntryNameLength;
    unsigned char                objectType;
    unsigned char                colorFlag;
    unsigned int                 leftSiblingId;
    unsigned int                 rightSiblingId;
    unsigned int                 childId;
    unsigned char                CLSID[16];
    unsigned int                 stateBits;
    EmbTime                      creationTime;
    EmbTime                      modifiedTime;
    unsigned int                 startingSectorLocation;
    /* streamSize should be long long but in our case we shouldn't need it,
     * and hard to support on c89 cross platform. */
    unsigned long                streamSize;
    /* Store the high int of streamsize. */
    unsigned int                 streamSizeHigh;
    struct _bcf_directory_entry* next;
} bcf_directory_entry;

/* TODO: possibly add a directory tree in the future.
 */
typedef struct _bcf_directory
{
    bcf_directory_entry* dirEntries;
    unsigned int         maxNumberOfDirectoryEntries;
} bcf_directory;

/* TODO: CLSID should be a separate type.
 */
typedef struct _bcf_file_header
{
    unsigned char  signature[8];
    unsigned char  CLSID[16];
    unsigned short minorVersion;
    unsigned short majorVersion;
    unsigned short byteOrder;
    unsigned short sectorShift;
    unsigned short miniSectorShift;
    unsigned short reserved1;
    unsigned int   reserved2;
    unsigned int   numberOfDirectorySectors;
    unsigned int   numberOfFATSectors;
    unsigned int   firstDirectorySectorLocation;
    unsigned int   transactionSignatureNumber;
    unsigned int   miniStreamCutoffSize;
    unsigned int   firstMiniFATSectorLocation;
    unsigned int   numberOfMiniFatSectors;
    unsigned int   firstDifatSectorLocation;
    unsigned int   numberOfDifatSectors;
} bcf_file_header;

/* . */
typedef struct _bcf_file
{
    bcf_file_header header;   /*! The header for the CompoundFile */
    bcf_file_difat* difat;    /*! The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /*! The File Allocation Table for the Compound File */
    bcf_directory* directory; /*! The directory for the CompoundFile */
} bcf_file;

/* . */
typedef struct _vp3Hoop
{
    int right;
    int bottom;
    int left;
    int top;
    int threadLength;
    char unknown2;
    unsigned char numberOfColors;
    unsigned short unknown3;
    int unknown4;
    int numberOfBytesRemaining;

    int xOffset;
    int yOffset;

    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;

    /* Centered hoop dimensions */
    int right2;
    int left2;
    int bottom2;
    int top2;

    int width;
    int height;
} vp3Hoop;

/* . */
typedef struct ThredHeader_     /* thred file header */
{
    unsigned int sigVersion;    /* signature and version */
    unsigned int length;        /* length of ThredHeader + length of stitch data */
    unsigned short numStiches;  /* number of stitches */
    unsigned short hoopSize;    /* size of hoop */
    unsigned short reserved[7]; /* reserved for expansion */
} ThredHeader;

/* . */
typedef struct ThredExtension_  /* thred v1.0 file header extension */
{
    float hoopX;                /* hoop size x dimension in 1/6 mm units */
    float hoopY;                /* hoop size y dimension in 1/6 mm units */
    float stitchGranularity;    /* stitches per millimeter--not implemented */
    char creatorName[50];       /* name of the file creator */
    char modifierName[50];      /* name of last file modifier */
    char auxFormat;             /* auxiliary file format, 0=PCS,1=DST,2=PES */
    char reserved[31];          /* reserved for expansion */
} ThredExtension;

/* . */
typedef struct SubDescriptor_
{
    int someNum;      /*! \todo better variable naming */
    int someInt;      /*! \todo better variable naming */
    int someOtherInt; /*! \todo better variable naming */
    char* colorCode;
    char* colorName;
} SubDescriptor;

/* . */
typedef struct StxThread_
{
    char* colorCode;
    char* colorName;
    char* sectionName;
    SubDescriptor* subDescriptors;
    EmbColor stxColor;
} StxThread;

/* . */
typedef struct VipHeader_ {
    int magicCode;
    int numberOfStitches;
    int numberOfColors;
    short postitiveXHoopSize;
    short postitiveYHoopSize;
    short negativeXHoopSize;
    short negativeYHoopSize;
    int attributeOffset;
    int xOffset;
    int yOffset;
    unsigned char stringVal[8];
    short unknown;
    int colorLength;
} VipHeader;

/* . */
typedef enum
{
    CSV_EXPECT_NULL,
    CSV_EXPECT_QUOTE1,
    CSV_EXPECT_QUOTE2,
    CSV_EXPECT_COMMA
} CSV_EXPECT;

/* . */
typedef enum
{
    CSV_MODE_NULL,
    CSV_MODE_COMMENT,
    CSV_MODE_VARIABLE,
    CSV_MODE_THREAD,
    CSV_MODE_STITCH
} CSV_MODE;

/* . */
typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

/* . */
typedef struct Huffman {
    int default_value;
    int lengths[1000];
    int nlengths;
    int table[1000];
    int table_width;
    int ntable;
} huffman;

/* . */
typedef struct Compress {
    int bit_position;
    char *input_data;
    int input_length;
    int bits_total;
    int block_elements;
    huffman character_length_huffman;
    huffman character_huffman;
    huffman distance_huffman;
} compress;

/* . */
typedef struct EmbImage_ {
    EmbVector position;
    EmbVector dimensions;
    unsigned char* data;
    int width;
    int height;
    char path[200];
    char name[200];
} EmbImage;

/* . */
typedef struct EmbBlock_ {
    EmbVector position;
} EmbBlock;

/* . */
typedef struct EmbAlignedDim_ {
    EmbVector position;
} EmbAlignedDim;

/* . */
typedef struct EmbAngularDim_ {
    EmbVector position;
} EmbAngularDim;

/* . */
typedef struct EmbArcLengthDim_ {
    EmbVector position;
} EmbArcLengthDim;

/* . */
typedef struct EmbDiameterDim_ {
    EmbVector position;
} EmbDiameterDim;

/* . */
typedef struct EmbLeaderDim_ {
    EmbVector position;
} EmbLeaderDim;

/* . */
typedef struct EmbLinearDim_ {
    EmbVector position;
} EmbLinearDim;

/* . */
typedef struct EmbOrdinateDim_ {
    EmbVector position;
} EmbOrdinateDim;

/* . */
typedef struct EmbRadiusDim_ {
    EmbVector position;
} EmbRadiusDim;

/* . */
typedef struct EmbInfiniteLine_ {
    EmbVector position;
} EmbInfiniteLine;

/* . */
typedef struct EmbRay_ {
    EmbVector position;
} EmbRay;

/* . */
typedef struct EmbTextMulti_ {
    EmbVector position;
    char text[200];
} EmbTextMulti;

/* . */
typedef struct EmbTextSingle_ {
    EmbVector position;
    char text[200];
} EmbTextSingle;

/* . */
typedef struct EmbPoint_
{
    EmbVector position;
    int lineType;
    EmbColor color;
} EmbPoint;

/* . */
typedef struct EmbLine_
{
    EmbVector start;
    EmbVector end;
    int lineType;
    EmbColor color;
} EmbLine;

/* . */
typedef struct EmbPath_
{
    EmbArray* pointList;
    EmbArray* flagList;
    int lineType;
    EmbColor color;
} EmbPath;

/* . */
typedef struct EmbStitch_
{
    int flags; /*! uses codes defined above */
    EmbReal x; /*! absolute position (not relative) */
    EmbReal y; /*! positive is up, units are in mm  */
    int color; /*! color number for this stitch */
    /*! \todo this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

/* . */
typedef struct EmbThread_
{
    EmbColor color;
    char description[50];
    char catalogNumber[30];
} EmbThread;

/* . */
typedef struct thread_color_ {
    char name[22];
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

/* absolute position (not relative) */
typedef struct EmbArc_
{
    EmbVector start;
    EmbVector mid;
    EmbVector end;
} EmbArc;

/* . */
typedef struct EmbRect_
{
    EmbReal top;
    EmbReal left;
    EmbReal bottom;
    EmbReal right;
    EmbReal rotation;
    EmbReal radius;
} EmbRect;

/* . */
typedef struct EmbCircle_
{
    EmbVector center;
    EmbReal radius;
} EmbCircle;

/* . */
typedef EmbPath EmbPolygon;

/* . */
typedef EmbPath EmbPolyline;

/* . */
typedef int EmbFlag;

/* . */
typedef struct EmbSatinOutline_
{
    int length;
    EmbArray* side1;
    EmbArray* side2;
} EmbSatinOutline;

/* . */
typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
    EmbReal rotation;
} EmbEllipse;

/* . */
typedef struct EmbBezier_ {
    EmbVector start;
    EmbVector control1;
    EmbVector control2;
    EmbVector end;
} EmbBezier;

/* . */
typedef struct EmbSpline_ {
    EmbArray *beziers;
} EmbSpline;

/* . */
typedef struct LSYSTEM {
    char axiom;
    char *alphabet;
    char *constants;
    char **rules;
} L_system;

/* . */
typedef struct EmbGeometry_ {
    union {
        EmbArc arc;
        EmbCircle circle;
        EmbColor color;
        EmbEllipse ellipse;
        EmbLine line;
        EmbPath path;
        EmbPoint point;
        EmbPolygon polygon;
        EmbPolyline polyline;
        EmbRect rect;
        EmbSpline spline;
        EmbVector vector;
    } object;
    EmbStitch stitch;
    EmbThread thread;
    int flag;
    int type;
    int lineType;
    EmbColor color;
} EmbGeometry;

/* . */
struct EmbArray_ {
    EmbGeometry *geometry;
    EmbStitch *stitch;
    EmbThread *thread;
    int count;
    int length;
    int type;
};

/* . */
typedef struct EmbLayer_
{
    char name[100];
    EmbArray *geometry;
} EmbLayer;

/* . */
typedef struct EmbPattern_
{
    unsigned int dstJumpsPerTrim;
    EmbVector home;
    EmbReal hoop_width;
    EmbReal hoop_height;
    EmbArray *thread_list;
    EmbArray *stitch_list;
    EmbArray *geometry;
    EmbLayer layer[EMB_MAX_LAYERS];
    int currentColorIndex;
} EmbPattern;

/* . */
typedef struct EmbFormatList_
{
    char extension[2 + EMBFORMAT_MAXEXT];
    char description[EMBFORMAT_MAXDESC];
    char reader_state;
    char writer_state;
    int type;
    int color_only;
    int check_for_color_file;
    int write_external_color_file;
} EmbFormatList;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC int lindenmayer_system(L_system L, char* state, int iteration, int complete);
EMB_PUBLIC int hilbert_curve(EmbPattern *pattern, int iterations);

EMB_PUBLIC int emb_identify_format(const char *ending);
EMB_PUBLIC void testMain(int level);
EMB_PUBLIC int convert(const char *inf, const char *outf);

EMB_PUBLIC EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);

EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_resize(EmbArray *g);
EMB_PUBLIC void embArray_copy(EmbArray *dst, EmbArray *src);
EMB_PUBLIC int embArray_addArc(EmbArray* g, EmbArc arc);
EMB_PUBLIC int embArray_addCircle(EmbArray* g, EmbCircle circle);
EMB_PUBLIC int embArray_addEllipse(EmbArray* g, EmbEllipse ellipse);
EMB_PUBLIC int embArray_addFlag(EmbArray* g, int flag);
EMB_PUBLIC int embArray_addLine(EmbArray* g, EmbLine line);
EMB_PUBLIC int embArray_addRect(EmbArray* g, EmbRect rect);
EMB_PUBLIC int embArray_addPath(EmbArray* g, EmbPath p);
EMB_PUBLIC int embArray_addPoint(EmbArray* g, EmbPoint p);
EMB_PUBLIC int embArray_addPolygon(EmbArray* g, EmbPolygon p);
EMB_PUBLIC int embArray_addPolyline(EmbArray* g, EmbPolyline p);
/* EMB_PUBLIC int embArray_addSpline(EmbArray* g, EmbSpline p); */
EMB_PUBLIC int embArray_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2);

EMB_PUBLIC EmbVector embLine_normalVector(EmbLine line, int clockwise);
EMB_PUBLIC EmbVector embLine_intersectionPoint(EmbLine line1, EmbLine line2);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbColor* colors, int n_colors);
EMB_PUBLIC int embThread_findNearestThread(EmbColor color, EmbThread* threads, int n_threads);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC EmbVector embVector_normalize(EmbVector vector);
EMB_PUBLIC EmbVector embVector_scale(EmbVector vector, EmbReal magnitude);
EMB_PUBLIC EmbVector embVector_add(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector embVector_average(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector embVector_subtract(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal embVector_cross(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector embVector_transpose_product(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal embVector_length(EmbVector vector);
EMB_PUBLIC EmbReal embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal embVector_angle(EmbVector v);
EMB_PUBLIC EmbReal embVector_distance(EmbVector a, EmbVector b);
EMB_PUBLIC EmbVector embVector_unit(EmbReal angle);

EMB_PUBLIC EmbArc embArc_init(void);
EMB_PUBLIC char embArc_clockwise(EmbArc arc);
EMB_PUBLIC EmbVector embArc_center(EmbArc arc);
EMB_PUBLIC EmbReal embArc_radius(EmbArc arc);
EMB_PUBLIC EmbReal embArc_diameter(EmbArc arc);
EMB_PUBLIC EmbReal embArc_chord(EmbArc arc);
EMB_PUBLIC EmbVector embArc_chordMid(EmbArc arc);
EMB_PUBLIC EmbReal embArc_sagitta(EmbArc arc);
EMB_PUBLIC EmbReal embArc_apothem(EmbArc arc);
EMB_PUBLIC EmbReal embArc_incAngle(EmbArc arc);
EMB_PUBLIC EmbReal embArc_bulge(EmbArc arc);

EMB_PUBLIC EmbCircle embCircle_init(void);
EMB_PUBLIC int getCircleCircleIntersections(
     EmbCircle c0, EmbCircle c1, EmbVector *v0, EmbVector *v1);
EMB_PUBLIC int getCircleTangentPoints(
     EmbCircle c, EmbVector p, EmbVector *v0, EmbVector *v1);

EMB_PUBLIC EmbEllipse embEllipse_init(void);
EMB_PUBLIC EmbEllipse embEllipse_make(EmbReal cx, EmbReal cy, EmbReal rx, EmbReal ry);
EMB_PUBLIC EmbReal embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_height(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_area(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_perimeter(EmbEllipse ellipse);

EMB_PUBLIC EmbImage embImage_create(int, int);
EMB_PUBLIC void embImage_read(EmbImage *image, char *fname);
EMB_PUBLIC int embImage_write(EmbImage *image, char *fname);
EMB_PUBLIC void embImage_free(EmbImage *image);

EMB_PUBLIC EmbRect embRect_init(void);
EMB_PUBLIC EmbReal embRect_area(EmbRect);

EMB_PUBLIC int threadColor(const char*, int brand);
EMB_PUBLIC int threadColorNum(unsigned int color, int brand);
EMB_PUBLIC const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines,
    EmbReal thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result,
    EmbReal density);

EMB_PUBLIC EmbGeometry *embGeometry_init(int type_in);
EMB_PUBLIC void embGeometry_free(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_move(EmbGeometry *obj, EmbVector delta);
EMB_PUBLIC EmbRect embGeometry_boundingRect(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_vulcanize(EmbGeometry *obj);

EMB_PUBLIC EmbPattern* embPattern_create(void);
EMB_PUBLIC void embPattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void embPattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int embPattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void embPattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y,
    int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void embPattern_free(EmbPattern* p);
EMB_PUBLIC void embPattern_scale(EmbPattern* p, EmbReal scale);
EMB_PUBLIC EmbReal embPattern_totalStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal embPattern_minimumStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal embPattern_maximumStitchLength(EmbPattern *pattern);
EMB_PUBLIC void embPattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS);
EMB_PUBLIC int embPattern_realStitches(EmbPattern *pattern);
EMB_PUBLIC int embPattern_jumpStitches(EmbPattern *pattern);
EMB_PUBLIC int embPattern_trimStitches(EmbPattern *pattern);
EMB_PUBLIC EmbRect embPattern_calcBoundingBox(EmbPattern* p);
EMB_PUBLIC void embPattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void embPattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void embPattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void embPattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void embPattern_correctForMaxStitchLength(EmbPattern* p, EmbReal maxStitchLength, EmbReal maxJumpLength);
EMB_PUBLIC void embPattern_center(EmbPattern* p);
EMB_PUBLIC void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC void embPattern_convertGeometry(EmbPattern* p);
EMB_PUBLIC void embPattern_designDetails(EmbPattern *p);
EMB_PUBLIC EmbPattern *embPattern_combine(EmbPattern *p1, EmbPattern *p2);
EMB_PUBLIC int embPattern_color_count(EmbPattern *pattern, EmbColor startColor);
EMB_PUBLIC void embPattern_end(EmbPattern* p);
EMB_PUBLIC void embPattern_crossstitch(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC void embPattern_horizontal_fill(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC int embPattern_render(EmbPattern *pattern, char *fname);
EMB_PUBLIC int embPattern_simulate(EmbPattern *pattern, char *fname);

EMB_PUBLIC void embPattern_addCircleAbs(EmbPattern* p, EmbCircle obj);
EMB_PUBLIC void embPattern_addEllipseAbs(EmbPattern* p, EmbEllipse obj);
EMB_PUBLIC void embPattern_addLineAbs(EmbPattern* p, EmbLine obj);
EMB_PUBLIC void embPattern_addPathAbs(EmbPattern* p, EmbPath obj);
EMB_PUBLIC void embPattern_addPointAbs(EmbPattern* p, EmbPoint obj);
EMB_PUBLIC void embPattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj);
EMB_PUBLIC void embPattern_addPolylineAbs(EmbPattern* p, EmbPolyline obj);
EMB_PUBLIC void embPattern_addRectAbs(EmbPattern* p, EmbRect obj);

EMB_PUBLIC void embPattern_copyStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_copyPolylinesToStitchList(EmbPattern* pattern);
EMB_PUBLIC void embPattern_moveStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_movePolylinesToStitchList(EmbPattern* pattern);

EMB_PUBLIC char embPattern_read(EmbPattern *pattern, const char* fileName, int format);
EMB_PUBLIC char embPattern_write(EmbPattern *pattern, const char* fileName, int format);

EMB_PUBLIC char embPattern_readAuto(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char embPattern_writeAuto(EmbPattern *pattern, const char* fileName);

EMB_PUBLIC void report(int result, char *label);
EMB_PUBLIC int full_test_matrix(char *fname);

EMB_PUBLIC int emb_round(EmbReal x);
EMB_PUBLIC EmbReal radians(EmbReal degree);
EMB_PUBLIC EmbReal degrees(EmbReal radian);

/* Utility Functions */
EMB_PUBLIC int stringInArray(const char *s, const char **array);
EMB_PUBLIC char *copy_trim(char const *s);
EMB_PUBLIC char* emb_optOut(EmbReal num, char* str);
EMB_PUBLIC void safe_free(void *data);

/* DIFAT functions */
EMB_PUBLIC unsigned int entriesInDifatSector(bcf_file_difat* fat);
EMB_PUBLIC bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
EMB_PUBLIC void loadFatFromSector(bcf_file_fat* fat, FILE* file);
EMB_PUBLIC void bcf_file_fat_free(bcf_file_fat** fat);
EMB_PUBLIC bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
EMB_PUBLIC void bcf_directory_free(bcf_directory** dir);
EMB_PUBLIC unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
EMB_PUBLIC void bcf_file_difat_free(bcf_file_difat* difat);
EMB_PUBLIC bcf_file_header bcfFileHeader_read(FILE* file);
EMB_PUBLIC int bcfFileHeader_isValid(bcf_file_header header);
EMB_PUBLIC void bcf_file_free(bcf_file* bcfFile);

EMB_PUBLIC void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1);
EMB_PUBLIC int create_test_file_1(const char* outf);
EMB_PUBLIC int create_test_file_2(const char* outf);
EMB_PUBLIC int create_test_file_3(const char* outf);
EMB_PUBLIC int testEmbCircle(void);
EMB_PUBLIC int testEmbCircle_2(void);
EMB_PUBLIC int testGeomArc(void);
EMB_PUBLIC int testThreadColor(void);
EMB_PUBLIC int testEmbFormat(void);

/* Encoding/decoding and compression functions. */
EMB_PUBLIC int hus_compress(char* input, int size, char* output, int *out_size);
EMB_PUBLIC int hus_decompress(char* input, int size, char* output, int *out_size);

EMB_PUBLIC void huffman_build_table(huffman *h);
EMB_PUBLIC int *huffman_table_lookup(huffman *h, int byte_lookup, int *lengths);

EMB_PUBLIC int compress_get_bits(compress *c, int length);
EMB_PUBLIC int compress_pop(compress *c, int bit_count);
EMB_PUBLIC int compress_read_variable_length(compress *c);
EMB_PUBLIC void compress_load_character_length_huffman(compress *c);
EMB_PUBLIC void compress_load_character_huffman(compress *c);
EMB_PUBLIC void compress_load_distance_huffman(compress *c);
EMB_PUBLIC void compress_load_block(compress *c);
EMB_PUBLIC int compress_get_token(compress *c);
EMB_PUBLIC int compress_get_position(compress *c);

EMB_PUBLIC EmbReal pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3);

EMB_PUBLIC int decodeNewStitch(unsigned char value);

EMB_PUBLIC unsigned char mitEncodeStitch(EmbReal value);
EMB_PUBLIC int mitDecodeStitch(unsigned char value);

EMB_PUBLIC void encode_t01_record(unsigned char b[3], int x, int y, int flags);
EMB_PUBLIC int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

EMB_PUBLIC int encode_tajima_ternary(unsigned char b[3], int x, int y);
EMB_PUBLIC void decode_tajima_ternary(unsigned char b[3], int *x, int *y);

/* NON-MACRO CONSTANTS
 ******************************************************************************/

extern EmbFormatList formatTable[numberOfFormats];
extern const int pecThreadCount;
extern const int shvThreadCount;
extern const EmbReal embConstantPi;
extern const EmbThread husThreads[];
extern const EmbThread jefThreads[];
extern const EmbThread shvThreads[];
extern const EmbThread pcmThreads[];
extern const EmbThread pecThreads[];
extern const unsigned char _dxfColorTable[][3];
extern EmbThread black_thread;
extern const unsigned char vipDecodingTable[];
extern const char imageWithFrame[38][48];


/* VARIABLES
 ******************************************************************************/

/* Error code storage for optional control flow blocking.
 *
 * This is potentially not thread-safe beacuse it is set by functions called
 * asyncronously and is global. If we only ever add to the variable then
 * an error cannot be missed because then at most one call per thread can
 * resolve before the check is performed and the status isn't overridden.
 */
extern int emb_error;

/* Verbosity level. */
extern int emb_verbose;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */
