


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "PppInterface.h"
#include "Taf_MmiStrParse.h"
#include "AppVcApi.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
#include "TafStdlib.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */

#include "at_common.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDPROC_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/* The following tables maps the 256 characters of PBM8 to the corresponding
 * unicode characters. */
/*lint -e569 �޸���:jinni 00168360;������:c48098 ԭ��pclint�澯���ֽ�����ת�����ܲ����������� */
AT_PB_CONVERSION_TABLE_STRU  g_astIraToUnicode[AT_PB_IRA_MAX_NUM] =
{
    {0x00, 0, 0x0000}, /* Null */
    {0x01, 0, 0x0001}, /* Start of heading */
    {0x02, 0, 0x0002}, /* Start of text */
    {0x03, 0, 0x0003}, /* End of text */
    {0x04, 0, 0x0004}, /* End of transmission */
    {0x05, 0, 0x0005}, /* Inquiry */
    {0x06, 0, 0x0006}, /* ACK */
    {0x07, 0, 0x0007}, /* Bell */
    {0x08, 0, 0x0008}, /* Backspace */
    {0x09, 0, 0x0009}, /* Tab */
    {0x0A, 0, 0x000A}, /* Line feed */
    {0x0B, 0, 0x000B}, /* Vertical tab */
    {0x0C, 0, 0x000C}, /* Form feed */
    {0x0D, 0, 0x000D}, /* Carriage return */
    {0x0E, 0, 0x000E}, /* Shift out */
    {0x0F, 0, 0x000F}, /* Shift in */
    {0x10, 0, 0x0010}, /* Data link escape */
    {0x11, 0, 0x0011}, /* Device control one */
    {0x12, 0, 0x0012}, /* Device control two */
    {0x13, 0, 0x0013}, /* Device control three */
    {0x14, 0, 0x0014}, /* Device control four */
    {0x15, 0, 0x0015}, /* NAK */
    {0x16, 0, 0x0016}, /* Synch */
    {0x17, 0, 0x0017}, /* End of block */
    {0x18, 0, 0x0018}, /* Cancel */
    {0x19, 0, 0x0019}, /* End of medium */
    {0x1A, 0, 0x001A}, /* Substitute */
    {0x1B, 0, 0x001B}, /* ESC */
    {0x1C, 0, 0x001C}, /* File separator */
    {0x1D, 0, 0x001D}, /* Group separator */
    {0x1E, 0, 0x001E}, /* Record separator */
    {0x1F, 0, 0x001F}, /* Unit separator */
    {0x20, 0, 0x0020}, /* Space */
    {0x21, 0, 0x0021}, /* Exclamation mark */
    {0x22, 0, 0x0022}, /* Quotation mark */
    {0x23, 0, 0x0023}, /* Number sign */
    {0x24, 0, 0x0024}, /* Dollar sign */
    {0x25, 0, 0x0025}, /* Percent sign */
    {0x26, 0, 0x0026}, /* Ampersand */
    {0x27, 0, 0x0027}, /* Apostrophe */
    {0x28, 0, 0x0028}, /* Left parenthesis */
    {0x29, 0, 0x0029}, /* Right parenthesis */
    {0x2A, 0, 0x002A}, /* Asterisk */
    {0x2B, 0, 0x002B}, /* Plus */
    {0x2C, 0, 0x002C}, /* Comma */
    {0x2D, 0, 0x002D}, /* Hyphen */
    {0x2E, 0, 0x002E}, /* Full stop */
    {0x2F, 0, 0x002F}, /* Solidus */
    {0x30, 0, 0x0030}, /* Zero */
    {0x31, 0, 0x0031}, /* One */
    {0x32, 0, 0x0032}, /* Two */
    {0x33, 0, 0x0033}, /* Three */
    {0x34, 0, 0x0034}, /* Four */
    {0x35, 0, 0x0035}, /* Five */
    {0x36, 0, 0x0036}, /* Six */
    {0x37, 0, 0x0037}, /* Seven */
    {0x38, 0, 0x0038}, /* Eight */
    {0x39, 0, 0x0039}, /* Nine */
    {0x3A, 0, 0x003A}, /* Colon */
    {0x3B, 0, 0x003B}, /* Semicolon */
    {0x3C, 0, 0x003C}, /* < (Less than) */
    {0x3D, 0, 0x003D}, /* = Equals */
    {0x3E, 0, 0x003E}, /* > greater than */
    {0x3F, 0, 0x003F}, /* Question mark */
    {0x40, 0, 0x0040}, /* AT Sign */
    {0x41, 0, 0x0041}, /* Latin A */
    {0x42, 0, 0x0042}, /* Latin B */
    {0x43, 0, 0x0043}, /* Latin C */
    {0x44, 0, 0x0044}, /* Latin D */
    {0x45, 0, 0x0045}, /* Latin E */
    {0x46, 0, 0x0046}, /* Latin F */
    {0x47, 0, 0x0047}, /* Latin G */
    {0x48, 0, 0x0048}, /* Latin H */
    {0x49, 0, 0x0049}, /* Latin I */
    {0x4A, 0, 0x004A}, /* Latin J */
    {0x4B, 0, 0x004B}, /* Latin K */
    {0x4C, 0, 0x004C}, /* Latin L */
    {0x4D, 0, 0x004D}, /* Latin M */
    {0x4E, 0, 0x004E}, /* Latin N */
    {0x4F, 0, 0x004F}, /* Latin O */
    {0x50, 0, 0x0050}, /* Latin P */
    {0x51, 0, 0x0051}, /* Latin Q */
    {0x52, 0, 0x0052}, /* Latin R */
    {0x53, 0, 0x0053}, /* Latin S */
    {0x54, 0, 0x0054}, /* Latin T */
    {0x55, 0, 0x0055}, /* Latin U */
    {0x56, 0, 0x0056}, /* Latin V */
    {0x57, 0, 0x0057}, /* Latin W */
    {0x58, 0, 0x0058}, /* Latin X */
    {0x59, 0, 0x0059}, /* Latin Y */
    {0x5A, 0, 0x005A}, /* Latin Z */
    {0x5B, 0, 0x005B}, /* Left square bracket */
    {0x5C, 0, 0x005C}, /* Reverse solidus */
    {0x5D, 0, 0x005D}, /* Right square bracket */
    {0x5E, 0, 0x005E}, /* Circumflex accent */
    {0x5F, 0, 0x005F}, /* Low line */
    {0x60, 0, 0x0060}, /* Grave accent */
    {0x61, 0, 0x0061}, /* Latin a */
    {0x62, 0, 0x0062}, /* Latin b */
    {0x63, 0, 0x0063}, /* Latin c */
    {0x64, 0, 0x0064}, /* Latin d */
    {0x65, 0, 0x0065}, /* Latin e */
    {0x66, 0, 0x0066}, /* Latin f */
    {0x67, 0, 0x0067}, /* Latin g */
    {0x68, 0, 0x0068}, /* Latin h */
    {0x69, 0, 0x0069}, /* Latin i */
    {0x6A, 0, 0x006A}, /* Latin j */
    {0x6B, 0, 0x006B}, /* Latin k */
    {0x6C, 0, 0x006C}, /* Latin l */
    {0x6D, 0, 0x006D}, /* Latin m */
    {0x6E, 0, 0x006E}, /* Latin n */
    {0x6F, 0, 0x006F}, /* Latin o */
    {0x70, 0, 0x0070}, /* Latin p */
    {0x71, 0, 0x0071}, /* Latin q */
    {0x72, 0, 0x0072}, /* Latin r */
    {0x73, 0, 0x0073}, /* Latin s */
    {0x74, 0, 0x0074}, /* Latin t */
    {0x75, 0, 0x0075}, /* Latin u */
    {0x76, 0, 0x0076}, /* Latin v */
    {0x77, 0, 0x0077}, /* Latin w */
    {0x78, 0, 0x0078}, /* Latin x */
    {0x79, 0, 0x0079}, /* Latin y */
    {0x7A, 0, 0x007A}, /* Latin z */
    {0x7B, 0, 0x007B}, /* Left curly bracket */
    {0x7C, 0, 0x007C}, /* Vertical line */
    {0x7D, 0, 0x007D}, /* Right curly bracket */
    {0x7E, 0, 0x007E}, /* Tilde */
    {0x7F, 0, 0x007F}, /* DEL */
    {0x80, 0, 0x0080}, /* control character 0x80 */
    {0x81, 0, 0x0081}, /* control character 0x81 */
    {0x82, 0, 0x0082}, /* control character 0x82 */
    {0x83, 0, 0x0083}, /* control character 0x83 */
    {0x84, 0, 0x0084}, /* control character 0x84 */
    {0x85, 0, 0x0085}, /* control character 0x85 */
    {0x86, 0, 0x0086}, /* control character 0x86 */
    {0x87, 0, 0x0087}, /* control character 0x87 */
    {0x88, 0, 0x0088}, /* control character 0x88 */
    {0x89, 0, 0x0089}, /* control character 0x89 */
    {0x8A, 0, 0x008A}, /* control character 0x8A */
    {0x8B, 0, 0x008B}, /* control character 0x8B */
    {0x8C, 0, 0x008C}, /* control character 0x8C */
    {0x8D, 0, 0x008D}, /* control character 0x8D */
    {0x8E, 0, 0x008E}, /* control character 0x8E */
    {0x8F, 0, 0x008F}, /* control character 0x8F */
    {0x90, 0, 0x0394}, /* Greek capital letter delta */
    {0x91, 0, 0x20AC}, /* Euro sign */
    {0x92, 0, 0x03A6}, /* Greek capital letter phi */
    {0x93, 0, 0x0393}, /* Greek capital letter gamma */
    {0x94, 0, 0x039B}, /* Greek capital letter lamda */
    {0x95, 0, 0x03A9}, /* Greek capital letter omega */
    {0x96, 0, 0x03A0}, /* Greek capital letter pi */
    {0x97, 0, 0x03A8}, /* Greek capital letter psi */
    {0x98, 0, 0x03A3}, /* Greek capital letter sigma */
    {0x99, 0, 0x0398}, /* Greek capital letter theta */
    {0x9A, 0, 0x039E}, /* Greek capital letter xi */
    {0x9B, 0, 0x009B}, /* control character 0x9B */
    {0x9C, 0, 0x009C}, /* control character 0x9C */
    {0x9D, 0, 0x009D}, /* control character 0x9D */
    {0x9E, 0, 0x009E}, /* control character 0x9E */
    {0x9F, 0, 0x009F}, /* control character 0x9F */
    {0xA0, 0, 0x00A0}, /* Non-Block Space */
    {0xA1, 0, 0x00A1}, /* Inverted exclamation mark */
    {0xA2, 0, 0x00A2}, /* Cent sign */
    {0xA3, 0, 0x00A3}, /* Pound sign */
    {0xA4, 0, 0x00A4}, /* Currency sign */
    {0xA5, 0, 0x00A5}, /* Yen sign */
    {0xA6, 0, 0x00A6}, /* Broken Vertical bar */
    {0xA7, 0, 0x00A7}, /* Section sign */
    {0xA8, 0, 0x00A8}, /* Diaeresis */
    {0xA9, 0, 0x00A9}, /* Copyright sign */
    {0xAA, 0, 0x00AA}, /* Feminine ordinal indicator */
    {0xAB, 0, 0x00AB}, /* Left-pointing double angle quotation mark */
    {0xAC, 0, 0x00AC}, /* Not sign */
    {0xAD, 0, 0x00AD}, /* Soft hyphen */
    {0xAE, 0, 0x00AE}, /* Registered sign */
    {0xAF, 0, 0x00AF}, /* Macron */
    {0xB0, 0, 0x00B0}, /* Degree sign */
    {0xB1, 0, 0x00B1}, /* Plus-minus sign */
    {0xB2, 0, 0x00B2}, /* Superscript two */
    {0xB3, 0, 0x00B3}, /* Superscript three */
    {0xB4, 0, 0x00B4}, /* Acute accent */
    {0xB5, 0, 0x00B5}, /* Micro sign */
    {0xB6, 0, 0x00B6}, /* Pilcrow sign */
    {0xB7, 0, 0x00B7}, /* Middle dot */
    {0xB8, 0, 0x00B8}, /* Cedilla */
    {0xB9, 0, 0x00B9}, /* Superscript one */
    {0xBA, 0, 0x00BA}, /* Masculine ordinal indicator */
    {0xBB, 0, 0x00BB}, /* Right-pointing double angle quotation mark */
    {0xBC, 0, 0x00BC}, /* Fraction one quarter */
    {0xBD, 0, 0x00BD}, /* Fraction one half */
    {0xBE, 0, 0x00BE}, /* Fraction three quarters */
    {0xBF, 0, 0x00BF}, /* Inverted question mark */
    {0xC0, 0, 0x00C0}, /* Latin A With grave */
    {0xC1, 0, 0x00C1}, /* Latin A With acute */
    {0xC2, 0, 0x00C2}, /* Latin A With circumflex */
    {0xC3, 0, 0x00C3}, /* Latin A With tilde */
    {0xC4, 0, 0x00C4}, /* Latin A With diaeresis */
    {0xC5, 0, 0x00C5}, /* Latin A With ring above */
    {0xC6, 0, 0x00C6}, /* Latin AE */
    {0xC7, 0, 0x00C7}, /* Latin C with cedilla */
    {0xC8, 0, 0x00C8}, /* Latin E with grave */
    {0xC9, 0, 0x00C9}, /* Latin E with acute */
    {0xCA, 0, 0x00CA}, /* Latin E with circumflex */
    {0xCB, 0, 0x00CB}, /* Latin E with diaeresis */
    {0xCC, 0, 0x00CC}, /* Latin I with grave */
    {0xCD, 0, 0x00CD}, /* Latin I with acute */
    {0xCE, 0, 0x00CE}, /* Latin I with circumflex */
    {0xCF, 0, 0x00CF}, /* Latin I with diaeresis */
    {0xD0, 0, 0x00D0}, /* Latin CAPITAL LETTER ETH (Icelandic) */
    {0xD1, 0, 0x00D1}, /* Latin CAPITAL LETTER N WITH TILDE */
    {0xD2, 0, 0x00D2}, /* Latin CAPITAL LETTER O WITH GRAVE */
    {0xD3, 0, 0x00D3}, /* Latin CAPITAL LETTER O WITH ACUTE */
    {0xD4, 0, 0x00D4}, /* Latin CAPITAL LETTER O WITH CIRCUMFLEX */
    {0xD5, 0, 0x00D5}, /* Latin CAPITAL LETTER O WITH TILDE */
    {0xD6, 0, 0x00D6}, /* Latin CAPITAL LETTER O WITH DIAERESIS */
    {0xD7, 0, 0x00D7}, /* MULTIPLICATION SIGN */
    {0xD8, 0, 0x00D8}, /* Latin CAPITAL LETTER O WITH STROKE */
    {0xD9, 0, 0x00D9}, /* Latin CAPITAL LETTER U WITH GRAVE */
    {0xDA, 0, 0x00DA}, /* Latin CAPITAL LETTER U WITH ACUTE */
    {0xDB, 0, 0x00DB}, /* Latin CAPITAL LETTER U WITH CIRCUMFLEX */
    {0xDC, 0, 0x00DC}, /* Latin CAPITAL LETTER U WITH DIAERESIS */
    {0xDD, 0, 0x00DD}, /* Latin CAPITAL LETTER Y WITH ACUTE */
    {0xDE, 0, 0x00DE}, /* Latin CAPITAL LETTER THORN (Icelandic) */
    {0xDF, 0, 0x00DF}, /* Latin SHARP S (German) */
    {0xE0, 0, 0x00E0}, /* Latin A WITH GRAVE */
    {0xE1, 0, 0x00E1}, /* Latin A WITH ACUTE */
    {0xE2, 0, 0x00E2}, /* Latin A WITH CIRCUMFLEX */
    {0xE3, 0, 0x00E3}, /* Latin A WITH TILDE */
    {0xE4, 0, 0x00E4}, /* Latin A WITH DIAERESIS */
    {0xE5, 0, 0x00E5}, /* Latin A WITH RING ABOVE */
    {0xE6, 0, 0x00E6}, /* Latin AE */
    {0xE7, 0, 0x00E7}, /* Latin C WITH CEDILLA */
    {0xE8, 0, 0x00E8}, /* Latin E WITH GRAVE */
    {0xE9, 0, 0x00E9}, /* Latin E WITH ACUTE */
    {0xEA, 0, 0x00EA}, /* Latin E WITH CIRCUMFLEX */
    {0xEB, 0, 0x00EB}, /* Latin E WITH DIAERESIS */
    {0xEC, 0, 0x00EC}, /* Latin I WITH GRAVE */
    {0xED, 0, 0x00ED}, /* Latin I WITH ACUTE */
    {0xEE, 0, 0x00EE}, /* Latin I WITH CIRCUMFLEX */
    {0xEF, 0, 0x00EF}, /* Latin I WITH DIAERESIS */
    {0xF0, 0, 0x00F0}, /* Latin ETH (Icelandic) */
    {0xF1, 0, 0x00F1}, /* Latin N WITH TILDE */
    {0xF2, 0, 0x00F2}, /* Latin O WITH GRAVE */
    {0xF3, 0, 0x00F3}, /* Latin O WITH ACUTE */
    {0xF4, 0, 0x00F4}, /* Latin O WITH CIRCUMFLEX */
    {0xF5, 0, 0x00F5}, /* Latin O WITH TILDE */
    {0xF6, 0, 0x00F6}, /* Latin O WITH DIAERESIS */
    {0xF7, 0, 0x00F7}, /* DIVISION SIGN */
    {0xF8, 0, 0x00F8}, /* Latin O WITH STROKE */
    {0xF9, 0, 0x00F9}, /* Latin U WITH GRAVE */
    {0xFA, 0, 0x00FA}, /* Latin U WITH ACUTE */
    {0xFB, 0, 0x00FB}, /* Latin U WITH CIRCUMFLEX */
    {0xFC, 0, 0x00FC}, /* Latin U WITH DIAERESIS */
    {0xFD, 0, 0x00FD}, /* Latin Y WITH ACUTE */
    {0xFE, 0, 0x00FE}, /* Latin THORN (Icelandic) */
    {0xFF, 0, 0x00FF}, /* Latin Y WITH DIAERESIS */
};
/*lint +e569 �޸���:jinni 00168360;������:c48098 ԭ��pclint�澯���ֽ�����ת�����ܲ����������� */

/* The following table maps the gsm7 alphabet to the corresponding unicode
 * characters. This table is exactly 128 entries large. */
/*lint -e569 �޸���:jinni 00168360;������:c48098 ԭ��pclint�澯���ֽ�����ת�����ܲ����������� */
AT_PB_CONVERSION_TABLE_STRU g_astGsmToUnicode[AT_PB_GSM_MAX_NUM] =
{
    {0x00, 0, 0x0040}, /* COMMERCIAL AT */
    {0x01, 0, 0x00A3}, /* POUND SIGN */
    {0x02, 0, 0x0024}, /* DOLLAR SIGN */
    {0x03, 0, 0x00A5}, /* YEN SIGN */
    {0x04, 0, 0x00E8}, /* Latin E WITH GRAVE */
    {0x05, 0, 0x00E9}, /* Latin E WITH ACUTE */
    {0x06, 0, 0x00F9}, /* Latin U WITH GRAVE */
    {0x07, 0, 0x00EC}, /* Latin I WITH GRAVE */
    {0x08, 0, 0x00F2}, /* Latin O WITH GRAVE */
    {0x09, 0, 0x00E7}, /* Latin C WITH CEDILLA */
    {0x0A, 0, 0x000A}, /* LINE FEED */
    {0x0B, 0, 0x00D8}, /* Latin CAPITAL LETTER O WITH STROKE */
    {0x0C, 0, 0x00F8}, /* Latin O WITH STROKE */
    {0x0D, 0, 0x000D}, /* CARRIAGE RETURN */
    {0x0E, 0, 0x00C5}, /* Latin CAPITAL LETTER A WITH RING ABOVE */
    {0x0F, 0, 0x00E5}, /* Latin A WITH RING ABOVE */
    {0x10, 0, 0x0394}, /* GREEK CAPITAL LETTER DELTA */
    {0x11, 0, 0x005F}, /* LOW LINE */
    {0x12, 0, 0x03A6}, /* GREEK CAPITAL LETTER PHI */
    {0x13, 0, 0x0393}, /* GREEK CAPITAL LETTER GAMMA */
    {0x14, 0, 0x039B}, /* GREEK CAPITAL LETTER LAMDA */
    {0x15, 0, 0x03A9}, /* GREEK CAPITAL LETTER OMEGA */
    {0x16, 0, 0x03A0}, /* GREEK CAPITAL LETTER PI */
    {0x17, 0, 0x03A8}, /* GREEK CAPITAL LETTER PSI */
    {0x18, 0, 0x03A3}, /* GREEK CAPITAL LETTER SIGMA */
    {0x19, 0, 0x0398}, /* GREEK CAPITAL LETTER THETA */
    {0x1A, 0, 0x039E}, /* GREEK CAPITAL LETTER XI */
    {0x1B, 0, 0x00A0}, /* ESCAPE TO EXTENSION TABLE */
    {0x1C, 0, 0x00C6}, /* Latin CAPITAL LETTER AE */
    {0x1D, 0, 0x00E6}, /* Latin AE */
    {0x1E, 0, 0x00DF}, /* Latin SHARP S (German) */
    {0x1F, 0, 0x00C9}, /* Latin CAPITAL LETTER E WITH ACUTE */
    {0x20, 0, 0x0020}, /* SPACE */
    {0x21, 0, 0x0021}, /* EXCLAMATION MARK */
    {0x22, 0, 0x0022}, /* QUOTATION MARK */
    {0x23, 0, 0x0023}, /* NUMBER SIGN */
    {0x24, 0, 0x00A4}, /* CURRENCY SIGN */
    {0x25, 0, 0x0025}, /* PERCENT SIGN */
    {0x26, 0, 0x0026}, /* AMPERSAND */
    {0x27, 0, 0x0027}, /* APOSTROPHE */
    {0x28, 0, 0x0028}, /* LEFT PARENTHESIS */
    {0x29, 0, 0x0029}, /* RIGHT PARENTHESIS */
    {0x2A, 0, 0x002A}, /* ASTERISK */
    {0x2B, 0, 0x002B}, /* PLUS SIGN */
    {0x2C, 0, 0x002C}, /* COMMA */
    {0x2D, 0, 0x002D}, /* HYPHEN-MINUS */
    {0x2E, 0, 0x002E}, /* FULL STOP */
    {0x2F, 0, 0x002F}, /* SOLIDUS */
    {0x30, 0, 0x0030}, /* DIGIT ZERO */
    {0x31, 0, 0x0031}, /* DIGIT ONE */
    {0x32, 0, 0x0032}, /* DIGIT TWO */
    {0x33, 0, 0x0033}, /* DIGIT THREE */
    {0x34, 0, 0x0034}, /* DIGIT FOUR */
    {0x35, 0, 0x0035}, /* DIGIT FIVE */
    {0x36, 0, 0x0036}, /* DIGIT SIX */
    {0x37, 0, 0x0037}, /* DIGIT SEVEN */
    {0x38, 0, 0x0038}, /* DIGIT EIGHT */
    {0x39, 0, 0x0039}, /* DIGIT NINE */
    {0x3A, 0, 0x003A}, /* COLON */
    {0x3B, 0, 0x003B}, /* SEMICOLON */
    {0x3C, 0, 0x003C}, /* LESS-THAN SIGN */
    {0x3D, 0, 0x003D}, /* EQUALS SIGN */
    {0x3E, 0, 0x003E}, /* GREATER-THAN SIGN */
    {0x3F, 0, 0x003F}, /* QUESTION MARK */
    {0x40, 0, 0x00A1}, /* INVERTED EXCLAMATION MARK */
    {0x41, 0, 0x0041}, /* Latin CAPITAL LETTER A */
    {0x42, 0, 0x0042}, /* Latin CAPITAL LETTER B */
    {0x43, 0, 0x0043}, /* Latin CAPITAL LETTER C */
    {0x44, 0, 0x0044}, /* Latin CAPITAL LETTER D */
    {0x45, 0, 0x0045}, /* Latin CAPITAL LETTER E */
    {0x46, 0, 0x0046}, /* Latin CAPITAL LETTER F */
    {0x47, 0, 0x0047}, /* Latin CAPITAL LETTER G */
    {0x48, 0, 0x0048}, /* Latin CAPITAL LETTER H */
    {0x49, 0, 0x0049}, /* Latin CAPITAL LETTER I */
    {0x4A, 0, 0x004A}, /* Latin CAPITAL LETTER J */
    {0x4B, 0, 0x004B}, /* Latin CAPITAL LETTER K */
    {0x4C, 0, 0x004C}, /* Latin CAPITAL LETTER L */
    {0x4D, 0, 0x004D}, /* Latin CAPITAL LETTER M */
    {0x4E, 0, 0x004E}, /* Latin CAPITAL LETTER N */
    {0x4F, 0, 0x004F}, /* Latin CAPITAL LETTER O */
    {0x50, 0, 0x0050}, /* Latin CAPITAL LETTER P */
    {0x51, 0, 0x0051}, /* Latin CAPITAL LETTER Q */
    {0x52, 0, 0x0052}, /* Latin CAPITAL LETTER R */
    {0x53, 0, 0x0053}, /* Latin CAPITAL LETTER S */
    {0x54, 0, 0x0054}, /* Latin CAPITAL LETTER T */
    {0x55, 0, 0x0055}, /* Latin CAPITAL LETTER U */
    {0x56, 0, 0x0056}, /* Latin CAPITAL LETTER V */
    {0x57, 0, 0x0057}, /* Latin CAPITAL LETTER W */
    {0x58, 0, 0x0058}, /* Latin CAPITAL LETTER X */
    {0x59, 0, 0x0059}, /* Latin CAPITAL LETTER Y */
    {0x5A, 0, 0x005A}, /* Latin CAPITAL LETTER Z */
    {0x5B, 0, 0x00C4}, /* Latin CAPITAL LETTER A WITH DIAERESIS */
    {0x5C, 0, 0x00D6}, /* Latin CAPITAL LETTER O WITH DIAERESIS */
    {0x5D, 0, 0x00D1}, /* Latin CAPITAL LETTER N WITH TILDE */
    {0x5E, 0, 0x00DC}, /* Latin CAPITAL LETTER U WITH DIAERESIS */
    {0x5F, 0, 0x00A7}, /* SECTION SIGN */
    {0x60, 0, 0x00BF}, /* INVERTED QUESTION MARK */
    {0x61, 0, 0x0061}, /* Latin A */
    {0x62, 0, 0x0062}, /* Latin B */
    {0x63, 0, 0x0063}, /* Latin C */
    {0x64, 0, 0x0064}, /* Latin D */
    {0x65, 0, 0x0065}, /* Latin E */
    {0x66, 0, 0x0066}, /* Latin F */
    {0x67, 0, 0x0067}, /* Latin G */
    {0x68, 0, 0x0068}, /* Latin H */
    {0x69, 0, 0x0069}, /* Latin I */
    {0x6A, 0, 0x006A}, /* Latin J */
    {0x6B, 0, 0x006B}, /* Latin K */
    {0x6C, 0, 0x006C}, /* Latin L */
    {0x6D, 0, 0x006D}, /* Latin M */
    {0x6E, 0, 0x006E}, /* Latin N */
    {0x6F, 0, 0x006F}, /* Latin O */
    {0x70, 0, 0x0070}, /* Latin P */
    {0x71, 0, 0x0071}, /* Latin Q */
    {0x72, 0, 0x0072}, /* Latin R */
    {0x73, 0, 0x0073}, /* Latin S */
    {0x74, 0, 0x0074}, /* Latin T */
    {0x75, 0, 0x0075}, /* Latin U */
    {0x76, 0, 0x0076}, /* Latin V */
    {0x77, 0, 0x0077}, /* Latin W */
    {0x78, 0, 0x0078}, /* Latin X */
    {0x79, 0, 0x0079}, /* Latin Y */
    {0x7A, 0, 0x007A}, /* Latin Z */
    {0x7B, 0, 0x00E4}, /* Latin A WITH DIAERESIS */
    {0x7C, 0, 0x00F6}, /* Latin O WITH DIAERESIS */
    {0x7D, 0, 0x00F1}, /* Latin N WITH TILDE */
    {0x7E, 0, 0x00FC}, /* Latin U WITH DIAERESIS */
    {0x7F, 0, 0x00E0}, /* Latin A WITH GRAVE */
};

/* GSM7BIT ��UCS2ת������չ��,GSM7BIT��չ����չ��־Ϊ0x1b�����±�GSM7BIT������
��������0x1B65ʱ�����Ӧ��UCS2����Ϊ0x20AC�������ִ���ŷԪ�� */
AT_PB_CONVERSION_TABLE_STRU g_astGsm7extToUnicode[AT_PB_GSM7EXT_MAX_NUM] =
{
    {0x65, 0, 0x20AC}, /* EURO SIGN */
    {0x0A, 0, 0x000C}, /* FORM FEED */
    {0x14, 0, 0x005E}, /* CIRCUMFLEX ACCENT */
    {0x28, 0, 0x007B}, /* LEFT CURLY BRACKET */
    {0x29, 0, 0x007D}, /* RIGHT CURLY BRACKET */
    {0x2F, 0, 0x005C}, /* REVERSE SOLIDUS */
    {0x3C, 0, 0x005B}, /* LEFT SQUARE BRACKET */
    {0x3D, 0, 0x007E}, /* TILDE */
    {0x3E, 0, 0x005D}, /* RIGHT SQUARE BRACKET */
    {0x40, 0, 0x007C}, /* VERTICAL LINE */
};
/*lint +e569 �޸���:jinni 00168360;������:c48098 ԭ��pclint�澯���ֽ�����ת�����ܲ����������� */

const AT_STRING_TYPE_STRU gastAtStringTab[]=
{
    {AT_STRING_SM,(TAF_UINT8*)"\"SM\""},
    {AT_STRING_ME,(TAF_UINT8*)"\"ME\""},
    {AT_STRING_ON,(TAF_UINT8*)"\"ON\""},
    {AT_STRING_EN,(TAF_UINT8*)"\"EN\""},
    {AT_STRING_FD,(TAF_UINT8*)"\"FD\""},
    {AT_STRING_BD,(TAF_UINT8*)"\"BD\""},
    {AT_STRING_REC_UNREAD_TEXT,(TAF_UINT8*)"\"REC UNREAD\""},
    {AT_STRING_REC_READ_TEXT,(TAF_UINT8*)"\"REC READ\""},
    {AT_STRING_STO_UNSENT_TEXT,(TAF_UINT8*)"\"STO UNSENT\""},
    {AT_STRING_STO_SENT_TEXT,(TAF_UINT8*)"\"STO SENT\""},
    {AT_STRING_ALL_TEXT,(TAF_UINT8*)"\"ALL\""},
    {AT_STRING_REC_UNREAD_PDU,(TAF_UINT8*)"0"},
    {AT_STRING_REC_READ_PDU,(TAF_UINT8*)"1"},
    {AT_STRING_STO_UNSENT_PDU,(TAF_UINT8*)"2"},
    {AT_STRING_STO_SENT_PDU,(TAF_UINT8*)"3"},
    {AT_STRING_ALL_PDU,(TAF_UINT8*)"4"},
    {AT_STRING_IP,(TAF_UINT8*)"\"IP\""},
    {AT_STRING_PPP,(TAF_UINT8*)"\"PPP\""},
    {AT_STRING_IPV6,(VOS_UINT8*)"\"IPV6\""},
    {AT_STRING_IPV4V6,(VOS_UINT8*)"\"IPV4V6\""},

    {AT_STRING_0E0,(TAF_UINT8*)"\"0E0\""},
    {AT_STRING_1E2,(TAF_UINT8*)"\"1E2\""},
    {AT_STRING_7E3,(TAF_UINT8*)"\"7E3\""},
    {AT_STRING_1E3,(TAF_UINT8*)"\"1E3\""},
    {AT_STRING_1E4,(TAF_UINT8*)"\"1E4\""},
    {AT_STRING_1E5,(TAF_UINT8*)"\"1E5\""},
    {AT_STRING_1E6,(TAF_UINT8*)"\"1E6\""},
    {AT_STRING_1E1,(TAF_UINT8*)"\"1E1\""},
    {AT_STRING_5E2,(TAF_UINT8*)"\"5E2\""},
    {AT_STRING_5E3,(TAF_UINT8*)"\"5E3\""},
    {AT_STRING_4E3,(TAF_UINT8*)"\"4E3\""},
    {AT_STRING_6E8,(TAF_UINT8*)"\"6E8\""},

    {AT_STRING_CREG,(TAF_UINT8*)"+CREG: "},
    {AT_STRING_CGREG,(TAF_UINT8*)"+CGREG: "},
    {AT_STRING_CEREG,(TAF_UINT8*)"+CEREG: "},
    {AT_STRING_SRVST,(TAF_UINT8*)"^SRVST: "},
    {AT_STRING_MODE,(TAF_UINT8*)"^MODE: "},
    {AT_STRING_RSSI,(TAF_UINT8*)"^RSSI: "},
    {AT_STRING_TIME,(TAF_UINT8*)"^TIME: "},
    {AT_STRING_CTZV,(TAF_UINT8*)"+CTZV: "},
    {AT_STRING_CTZE,(TAF_UINT8*)"+CTZE: "},
    /* added by c00173809 for ע�����ԭ��ֵ�ϱ� 2011-08-3 begin */
    {AT_STRING_ERRRPT,(TAF_UINT8*)"^ERRRPT:"},
    /* added by c00173809 for ע�����ԭ��ֵ�ϱ� 2011-08-3 end */

    {AT_STRING_CCALLSTATE, (VOS_UINT8 *)"^CCALLSTATE"},

    {AT_STRING_CERSSI, (VOS_UINT8 *)"^CERSSI:"},

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-14, begin */
    {AT_STRING_ACINFO, (VOS_UINT8 *)"^ACINFO:"},
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-14, end */

    /* Added by l00171473 for DTS2013010800120 ����������Ϣ�ϱ�, 2013-1-5, begin */
    {AT_STRING_CS_CHANNEL_INFO, (VOS_UINT8 *)"^CSCHANNELINFO:"},
    /* Added by l00171473 for DTS2013010800120 ����������Ϣ�ϱ�, 2013-1-5, end */

    {AT_STRING_RESET, (VOS_UINT8 *)"^RESET:"},

    {AT_STRING_REFCLKFREQ, (VOS_UINT8 *)"^REFCLKFREQ"},

    {AT_STRING_REJINFO, (VOS_UINT8 *)"^REJINFO:"},

    {AT_STRING_PLMNSELEINFO, (VOS_UINT8 *)"^PLMNSELEINFO:"},

    {AT_STRING_NETSCAN, (VOS_UINT8 *)"^NETSCAN: "},

    {AT_STRING_CIREPH, (VOS_UINT8 *)"+CIREPH"},
    {AT_STRING_CIREPI, (VOS_UINT8 *)"+CIREPI"},
    {AT_STRING_CIREGU, (VOS_UINT8 *)"+CIREGU"},

    {AT_STRING_CALL_MODIFY_IND, (VOS_UINT8 *)"^CALLMODIFYIND:"},
    {AT_STRING_CALL_MODIFY_BEG, (VOS_UINT8 *)"^CALLMODIFYBEG:"},
    {AT_STRING_CALL_MODIFY_END, (VOS_UINT8 *)"^CALLMODIFYEND:"},

    {AT_STRING_ECONFSTATE, (VOS_UINT8 *)"^ECONFSTATE:"},


    {AT_STRING_CDISP,       (TAF_UINT8*)"^CDISP: "},
    {AT_STRING_CCONNNUM,    (TAF_UINT8*)"^CCONNNUM: "},
    {AT_STRING_CCALLEDNUM,  (TAF_UINT8*)"^CCALLEDNUM: "},
    {AT_STRING_CCALLINGNUM, (TAF_UINT8*)"^CCALLINGNUM: "},
    {AT_STRING_CREDIRNUM,   (TAF_UINT8*)"^CREDIRNUM: "},
    {AT_STRING_CSIGTONE,    (TAF_UINT8*)"^CSIGTONE: "},
    {AT_STRING_CLCTR,       (TAF_UINT8*)"^CLCTR: "},
    {AT_STRING_CCWAC,       (TAF_UINT8*)"^CCWAC: "},
    {AT_STRING_FILECHANGE, (VOS_UINT8 *)"^FILECHANGE:"},


    {AT_STRING_SRCHEDPLMNINFO, (VOS_UINT8 *)"^SRCHEDPLMNINFO:"},

    {AT_STRING_MCC,       (TAF_UINT8*)"^MCC:"},

    {AT_STRING_CMOLRE,      (VOS_UINT8 *)"+CMOLRE: "},
    {AT_STRING_CMOLRN,      (VOS_UINT8 *)"+CMOLRN: "},
    {AT_STRING_CMOLRG,      (VOS_UINT8 *)"+CMOLRG: "},
    {AT_STRING_CMTLR,       (VOS_UINT8 *)"+CMTLR: "},

    {AT_STRING_IMS_HOLD_TONE, (VOS_UINT8 *)"^IMSHOLDTONE"},

    {AT_STRING_BUTT,(TAF_UINT8*)"\"\""},
};

VOS_UINT8                               gaucAtCrLf[] = "\r\n";                  /*�س�����*/
const TAF_UINT8                         gaucAtCmeErrorStr[] = "+CME ERROR: ";   /*������ʾ�ִ�*/
const TAF_UINT8                         gaucAtCmsErrorStr[] = "+CMS ERROR: ";   /*������ʾ�ִ�*/

const TAF_UINT8                         gaucAtTooManyParaStr[]   = "TOO MANY PARAMETERS"; /*����̫����ʾ�ִ�*/

AT_CMD_FORMAT_TYPE                      gucAtCmdFmtType = AT_CMD_TYPE_BUTT;

AT_SEND_DATA_BUFFER_STRU                gstAtSendData;                          /* ��������ķ�����Ϣ�洢�� */
AT_SEND_DATA_BUFFER_STRU                gstAtCombineSendData[AT_MAX_CLIENT_NUM];/* �������ķ�����Ϣ�洢�� */

/* gstAtSendData.aucBuffer�ĵ�0��ΪMUX��֡ͷ��־ */
TAF_UINT8                              *pgucAtSndCrLfAddr = &gstAtSendData.aucBuffer[1];
TAF_UINT8                              *pgucAtSndCodeAddr = &gstAtSendData.aucBuffer[3];

/*���õ���Ĵ������ݷ��ͽӿ�ʱ���������ָ�����Ϊ4�ֽڶ����ʽ��
��pgucAtSndCrLfAddr��pgucAtSndCodeAddr��û������4�ֽڶ��룬������
��һ�ο���������(AT����������Ҫ�󲻸ߣ�������һ�ο����ǿ��е�)*/
TAF_UINT8                               gstAtSendDataBuffer[AT_CMD_MAX_LEN];

AT_V_TYPE                               gucAtVType      = AT_V_ENTIRE_TYPE;     /* ָʾ����������� */
AT_CSCS_TYPE                            gucAtCscsType   = AT_CSCS_IRA_CODE;     /* ָʾTE�������� */

AT_CMD_ECHO_TYPE                        gucAtEType      = AT_E_ECHO_CMD;
VOS_UINT32                              gucAtXType      = 0;   /* CONNECT <text> result code is given upon entering online data state.
                                                   Dial tone and busy detection are disabled. */
VOS_UINT32                              gucAtQType      = 0;   /* DCE transmits result codes */


/*->f62575*/
MN_OPERATION_ID_T                       g_OpId = 0;

MN_MSG_RAW_TS_DATA_STRU                 g_astAtMsgRawTsData[AT_MSG_MAX_MSG_SEGMENT_NUM];
MN_MSG_TS_DATA_INFO_STRU                g_stAtMsgTsDataInfo;
MN_MSG_SEND_PARM_STRU                   g_stAtMsgDirectParm;
MN_MSG_WRITE_PARM_STRU                  g_stAtMsgWriteParm;
MN_MSG_SEND_ACK_PARM_STRU               g_stAtMsgAckParm;

/*<-f62575*/
AT_CSTA_NUM_TYPE_ENUM_U8                g_enAtCstaNumType = (0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | (MN_CALL_NPI_ISDN));
AT_PB_INFO_STRU                         gstPBATInfo;
VOS_UINT8                               g_ucXsmsRecNum = 0;


/* �洢^PORTSEL���õĶ˿ںţ�������^PORTSEL? ��ѯʹ�á� */
TAF_UINT8                               gucAtPortSel  = 0;

/*��¼���翨�汾���ϵ絽���ųɹ�����ʱ�䣬��λ�� */
VOS_UINT32                              g_ulLcStartTime = 0;

TAF_UINT8                               gastAtPppIndexTab[AT_MAX_CLIENT_NUM];   /* PppId��Index�Ķ�Ӧ���±���PppId */

AT_DEVICE_CMD_CTRL_STRU                 g_stAtDevCmdCtrl        = {0};
VOS_BOOL                                g_bAtDataLocked         = VOS_TRUE;     /* ��¼�Ƿ��������ʼֵΪδ������ͨ������^DATALOCK�����ɹ����޸ĸñ��� */
VOS_UINT8                               g_ucDtrDownFlag         = VOS_FALSE;    /* �����Ҷϵ绰ʱ����̨������DTR�ܽ��źţ���ʱAT�ø�ȫ�ֱ���ΪVOS_TRUE,����DCD�ܽţ�
                                                                                ֮��CST����AT�ӿ�AT_CstDlDataInd��������ʱ�ж������ȫ�ֱ���ΪVOS_TRUE,�򲻵�����ӿڷ��ͣ�
                                                                                ֱ���������*/

/* Added by L60609 for AT Project��2011-10-10,  Begin*/
/*���������˿ڶ�Ӧ�Ľ������ݺ�������AT_PHY_PORT_ENUMΪ������*/
CPM_RCV_FUNC                            g_apAtPortDataRcvFuncTab[AT_PHY_PORT_MAX]
                                                = {VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR};
/* Added by L60609 for AT Project��2011-10-10,  End*/

/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, begin */
/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, end */

AT_SP_WORD_CTX_STRU                     g_stSpWordCtx = {0};

/*****************************************************************************
   3 ��������������
*****************************************************************************/

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : At_GetOpId
 ��������  : ��ȡAT��ǰ��Operation ID, ��ʶ���β���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��14��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��3��14��
    ��    ��   : fuyingjun
    �޸�����   : ����OpIdΪ0�����;

*****************************************************************************/
MN_OPERATION_ID_T  At_GetOpId(
    VOS_VOID
)
{
    g_OpId++;
    g_OpId %= MN_OP_ID_BUTT;
    if (0 == g_OpId)
    {
        g_OpId++;
    }
    return (g_OpId);
}


/*****************************************************************************
 �� �� ��  : At_ClientIdToUserId
 ��������  : ����֪ClientId �����û�����
 �������  : TAF_UINT16 usClientId
             TAF_UINT8 *pucIndexId
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    ��   : 2011��10��6��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ���ӹ㲥client��ת��

  3.��    ��   : 2012��12��15��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II

  4.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
TAF_UINT32 At_ClientIdToUserId (
    TAF_UINT16                              usClientId,
    TAF_UINT8                              *pucIndexId
)
{
    TAF_UINT8                           i;

    /* �ж��Ƿ�Ϊ�㲥client id */
    /* MODEM 0�Ĺ㲥ClientId */
    if (AT_BROADCAST_CLIENT_ID_MODEM_0 == usClientId)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
        return AT_SUCCESS;
    }

    /* MODEM 1�Ĺ㲥ClientId */
    if(AT_BROADCAST_CLIENT_ID_MODEM_1 == usClientId)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_1;
        return AT_SUCCESS;
    }

    /* MODEM 2�Ĺ㲥ClientId */
    if(AT_BROADCAST_CLIENT_ID_MODEM_2 == usClientId)
    {
        *pucIndexId = AT_BROADCAST_CLIENT_INDEX_MODEM_2;
        return AT_SUCCESS;
    }


    /* �����û������ */
    for ( i = 0; i < AT_MAX_CLIENT_NUM ; i++ )
    {
        if ( AT_CLIENT_NULL == gastAtClientTab[i].ucUsed )
        {
            continue;
        }
        if ( gastAtClientTab[i].usClientId == usClientId )
        {
            *pucIndexId = i;        /* ���ؽ�� */
            return AT_SUCCESS;
        }
    }
    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_SendReportMsg
 Description    : AT���ղ������¼��ϱ���Ϣ
 Input          : ucIndex --- �û�ID
                  pData   --- ����
                  usLen   --- ����
                  ucType  --- ��Ϣ����
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_VOID At_SendReportMsg(TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen)
{
    MN_AT_IND_EVT_STRU                  *pstEvent;
    VOS_UINT_PTR                         ulTmpAddr;
    /* �����Զ����ITEM����4���ֽ� */

    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
    if (TAF_NULL_PTR == pstEvent)
    {
        AT_ERR_LOG("At_SendCmdMsg:ERROR:Alloc Msg");
        return;
    }

    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEvent->ulSenderPid       = AT_GetDestPid(((SI_PB_EVENT_INFO_STRU *)pData)->ClientId, I0_WUEPS_PID_TAF);
    pstEvent->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEvent->usMsgName         = ucType;
    pstEvent->usLen             = usLen;

    ulTmpAddr = (VOS_UINT_PTR)pstEvent->aucContent;
    PS_MEM_CPY((VOS_VOID *)ulTmpAddr, pData, usLen);

    /*������Ϣ��AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_AT, pstEvent ) )
    {
        AT_ERR_LOG("At_SendReportMsg:ERROR");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ReportSysCfgExTestCmdResult
 ��������  : syscfgex���������ϱ�,��ʽ:
             ^SYSCFGEX:(list of supported < acqorder >s),
              (list of supported( <band >,<band_name>)s),
              (list of supported < roam >s),
              (list of supported < srvdomain >s),
              (list of supported( <lteband >,<lteband_name>)s),
              <CR><LF><CR><LF>OK<CR><LF>
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 AT_ReportSysCfgExTestCmdResult(
    VOS_UINT8                           ucIndex
)
{

    return 0;
}



/*****************************************************************************
 Prototype      : At_ScanDelChar
 Description    : ɨ���˸��
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ScanDelChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT16 usChkLen  = 0;
    TAF_UINT16 usLen     = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* ���������� */
    while ( usChkLen++ < *pLen )
    {
        if( ucAtS5 == *pRead)       /*ɾ����һ�ַ�*/
        {
            if( usLen > 0 )
            {
                pWrite--;
                usLen--;
            }
        }
        else                        /*ѡ����Ч�ַ�*/
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_ScanCtlChar
 Description    : ɨ����Ʒ�
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ScanCtlChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pWrite    = pData;
    TAF_UINT8  *pRead     = pData;
    TAF_UINT16 usChkLen   = 0;
    TAF_UINT16 usLen      = 0;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* ��� */
    while( usChkLen++ < *pLen )
    {
        /*ѡ����Ч�ַ�*/
        if( 0x20 <= *pRead )
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_ScanBlankChar
 Description    : ɨ��ո��
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_ScanBlankChar( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pCheck     = pData;
    TAF_UINT8  *pWrite     = pData;
    TAF_UINT8  *pRead      = pData;
    TAF_UINT32 ulChkQout   = 0;
    TAF_UINT16 usChkLen    = 0;
    TAF_UINT16 usQoutNum   = 0;
    TAF_UINT16 usQoutCount = 0;
    TAF_UINT16 usLen       = 0;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* ������� */
    while( usQoutNum ++ < *pLen )
    {
        if('"' == *pCheck++)
        {
            ulChkQout++;
        }
    }
    if(1 == (ulChkQout % 2))
    {
        return AT_FAILURE;
    }

    /* ��� */
    while( usChkLen++ < *pLen )
    {
        /* ��ǰ�ǵڼ�������״̬ */
        if( '\"' == *pRead )
        {
            usQoutCount++;
        }

        /* ȥ��������Ŀո� */
        if(( (0x20 != *pRead) && (0 == (usQoutCount % 2)) ) || ( 1 == (usQoutCount % 2) ))
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_ScanResetCmd
 Description    : ɨ��&F
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_ScanResetCmd( TAF_UINT8 *pData, TAF_UINT16 *pLen)
{
    TAF_UINT8  *pSearch = TAF_NULL_PTR;
    TAF_UINT16 usLen    = *pLen;

    /* �ַ�����β */
    pData[usLen] = 0;

    /* ȫ����ʽ��Ϊ��д�ַ� */
    At_UpString(pData,usLen);

    pSearch = (TAF_UINT8 *)VOS_StrStr((TAF_CHAR*)pData,"&F");

    while(TAF_NULL_PTR != pSearch)
    {
        if( ('0' < *(pSearch+2)) && (*(pSearch+2) <= '9'))
        {
            return AT_FAILURE;  /* �������� */
        }
        if( '0' == *(pSearch+2))
        {
            *(pSearch+2) = 13;  /* ��Ϊ�����ַ��������ʽ�� */
        }
        pSearch = (TAF_UINT8 *)VOS_StrStr((TAF_CHAR*)(pSearch+2),"&F");
    }

    At_ScanCtlChar(pData,&usLen);

    *pLen  =  usLen;
    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : At_GetDirectSendMsg
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��18��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
MN_MSG_SEND_PARM_STRU * At_GetDirectSendMsgMem(
    TAF_VOID
)
{
    PS_MEM_SET(&g_stAtMsgDirectParm, 0x00, sizeof(g_stAtMsgDirectParm));
    return &g_stAtMsgDirectParm;
}

/*****************************************************************************
 �� �� ��  : At_GetMsgMem
 ��������  : ��ȡTP�����Ϣ���ݽṹ���ڴ��׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TP�����Ϣ���ݽṹ���ڴ��׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��12��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_TS_DATA_INFO_STRU * At_GetMsgMem(
    VOS_VOID
)
{
    PS_MEM_SET(&g_stAtMsgTsDataInfo, 0x00, sizeof(g_stAtMsgTsDataInfo));
    return &g_stAtMsgTsDataInfo;
}

/*****************************************************************************
 �� �� ��  : At_GetLongMsgSegMem
 ��������  : ��ȡ������Ϣ�ֶ����ݽṹ�����׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������Ϣ�ֶ����ݽṹ�����׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��15��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_RAW_TS_DATA_STRU *At_GetLongMsgSegMem(
    TAF_VOID
)
{
    PS_MEM_SET(g_astAtMsgRawTsData, 0x00, (sizeof(MN_MSG_RAW_TS_DATA_STRU)*AT_MSG_MAX_MSG_SEGMENT_NUM));
    return g_astAtMsgRawTsData;
}

/*****************************************************************************
 �� �� ��  : At_GetWriteMsgMem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��18��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_WRITE_PARM_STRU * At_GetWriteMsgMem(
    TAF_VOID
)
{
    PS_MEM_SET(&g_stAtMsgWriteParm, 0x00, sizeof(g_stAtMsgWriteParm));
    return &g_stAtMsgWriteParm;
}

/*****************************************************************************
 �� �� ��  : At_GetWriteMsgMem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��18��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_SEND_ACK_PARM_STRU * At_GetAckMsgMem(
    VOS_VOID
)
{
    PS_MEM_SET(&g_stAtMsgAckParm, 0x00, sizeof(g_stAtMsgAckParm));
    return &g_stAtMsgAckParm;
}


/*****************************************************************************
 �� �� ��  : At_SendPduMsgOrCmd
 ��������  : PDU����Ϣ������ķ���
 �������  : ucIndex - �û�����ֵ
             pData   - PDU����,
             ulLen   - PDU���ݳ���
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��9��25��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ�ţ�AT2D14190�����ŷ���ʧ�ܴ���ԭ��ֵ���˲�һ��
  3.��    ��   : 2009��10��10��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ�ţ�AT2D15015��MAC/LINUX��̨�ƶ����糤���ŷ��ͽ����һ�����ͳɹ�
  4.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
  5.��    ��   : 2011��03��01��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                 ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
  6.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32  At_SendPduMsgOrCmd(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    TAF_UINT32                          ulRet;
    MN_MSG_SEND_PARM_STRU               *pstSendDirectParm;
    TAF_UINT32                          uAddrlLen           = 0;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData;
    AT_MODEM_SMS_CTX_STRU               *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if ((AT_CMD_CMGS_PDU_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_CMGC_PDU_SET != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        AT_WARN_LOG("At_SendPduMsgOrCmd: invalid command operation.");
        return AT_ERROR;
    }

    /*Refer to protocol 31102 4.2.25 */
    if (gastAtClientTab[ucIndex].AtSmsData.ucPduLen > ulLen)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: invalid tpdu data length.");
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    pstSendDirectParm = At_GetDirectSendMsgMem();

    pstSendDirectParm->enDomain     = pstSmsCtx->stCgsmsSendDomain.enSendDomain;
    pstSendDirectParm->enMemStore   = MN_MSG_MEM_STORE_NONE;
    pstSendDirectParm->enClientType = MN_MSG_CLIENT_NORMAL;

    /*sca*/
    if (ulLen > gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        ulRet = At_GetScaFromInputStr(pData, &pstSendDirectParm->stMsgInfo.stScAddr, &uAddrlLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }

        if (ulLen != (gastAtClientTab[ucIndex].AtSmsData.ucPduLen + uAddrlLen))
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: invalid tpdu data length.");
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }
    }

    if (0 == pstSendDirectParm->stMsgInfo.stScAddr.ucBcdLen)
    {
        if (0 == pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: without sca.");
            return AT_CMS_SMSC_ADDRESS_UNKNOWN;
        }
        PS_MEM_CPY(&pstSendDirectParm->stMsgInfo.stScAddr,
                   &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                   sizeof(pstSendDirectParm->stMsgInfo.stScAddr));
    }

    pstSendDirectParm->stMsgInfo.stTsRawData.ulLen = gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    PS_MEM_CPY(pstSendDirectParm->stMsgInfo.stTsRawData.aucData,
               &pData[uAddrlLen],
               gastAtClientTab[ucIndex].AtSmsData.ucPduLen);
    if (AT_CMD_CMGS_PDU_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        pstSendDirectParm->stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_SUBMIT;
    }
    else
    {
        pstSendDirectParm->stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_COMMAND;
    }

    /*����PDU����Ч�Լ�飬ɾ�������ֶ�*/
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstSendDirectParm->stMsgInfo.stTsRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: fail to decode.");
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    pstRawData = At_GetLongMsgSegMem();
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    if(MN_ERR_NO_ERROR != ulRet)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: fail to encode.");
    }
    else
    {
        if (pstRawData->ulLen != pstSendDirectParm->stMsgInfo.stTsRawData.ulLen)
        {
            AT_NORM_LOG1("At_SendPduMsgOrCmd: pstSendParm->stMsgInfo.stTsRawData.ulLen not match:",
                         pstSendDirectParm->stMsgInfo.stTsRawData.ulLen);
            AT_NORM_LOG1("At_SendPduMsgOrCmd: pstRawData->ulLen not match:", pstRawData->ulLen);
            pstSendDirectParm->stMsgInfo.stTsRawData.ulLen = pstRawData->ulLen;
        }
    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Send(gastAtClientTab[ucIndex].usClientId,
                        opId,
                        pstSendDirectParm);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        if (MN_ERR_CLASS_SMS_NOAVAILDOMAIN == ulRet)
        {
            ulRet = AT_CMS_UNKNOWN_ERROR;
        }
        else
        {
            ulRet = AT_ERROR;
        }
    }
    return ulRet;
}


/*****************************************************************************
 �� �� ��  : At_SendPduCnma
 �������  : ucIndex - �û�����ֵ
             pData   - PDU����,
             ulLen   - PDU���ݳ���
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��14��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012111201995��DCM���Ž��ն�������

*****************************************************************************/
TAF_UINT32  At_SendPduMsgAck(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    MN_MSG_SEND_ACK_PARM_STRU           *pstAckParm;
    TAF_UINT32                          ulRet;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    if (ulLen != gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        AT_NORM_LOG("At_SendPduMsgAck: the length of PDU is not consistent.");
        return AT_CMS_OPERATION_NOT_ALLOWED;    /* �����ִ�̫�� */
    }

    /* ִ��������� */
    pstAckParm = At_GetAckMsgMem();

    /*gastAtClientTab[ucIndex].AtSmsData.ucNumTypeΪ0������Ѿ�����������ʱֱ�Ӵ����ˣ��˴�������*/
    if (1 == gastAtClientTab[ucIndex].AtSmsData.ucCnmaType)
    {
        pstAckParm->bRpAck = TAF_TRUE;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;
    }
    else
    {
        pstAckParm->bRpAck = TAF_FALSE;
        pstAckParm->enRpCause = MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ERR;
    }

    /*gastAtClientTab[ucIndex].AtSmsData.ucPduLenΪ0������Ѿ�����������ʱֱ�Ӵ����ˣ��˴�������*/
    pstAckParm->stTsRawData.ulLen = (TAF_UINT32)gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    PS_MEM_CPY(pstAckParm->stTsRawData.aucData, pData, ulLen);
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstAckParm->stTsRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_NORM_LOG("At_SendPduMsgOrCmd: Fail to decode.");
        return AT_ERROR;
    }

    if ((TAF_FALSE == pstAckParm->bRpAck)
     && (MN_MSG_TP_CAUSE_MEMORY_FULL == pstTsDataInfo->u.stDeliverRptErr.enFailCause))
    {
        pstAckParm->enRpCause = MN_MSG_RP_CAUSE_MEMORY_EXCEEDED;
    }

    gastAtClientTab[ucIndex].opId = opId;
    if (MN_ERR_NO_ERROR == MN_MSG_SendAck(gastAtClientTab[ucIndex].usClientId, opId, pstAckParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMA_PDU_SET;
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
        ulRet = AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        ulRet = AT_ERROR;
    }
    return ulRet;
}


/*****************************************************************************
 �� �� ��  : At_WritePduMsgToMem
 ��������  : дPDU��ʽ�Ķ���Ϣ��NVIM��USIM
 �������  : ucIndex - �û�����ֵ
             pData   - PDU����,
             ulLen   - PDU���ݳ���
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��10��10��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ�ţ�AT2D15015��MAC/LINUX��̨�ƶ����糤���ŷ��ͽ����һ�����ͳɹ�
  3.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32  At_WritePduMsgToMem(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
)
{
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    TAF_UINT32                          ulAddrLen           = 0;
    TAF_UINT32                          ulRet;
    MN_MSG_WRITE_PARM_STRU              *pstWriteParm;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    MN_MSG_TPDU_TYPE_ENUM_U8            aucMtiMapTpduType[4] = {MN_MSG_TPDU_DELIVER,
                                                                MN_MSG_TPDU_SUBMIT,
                                                                MN_MSG_TPDU_COMMAND,
                                                                MN_MSG_TPDU_MAX};
    TAF_UINT8                           ucFo;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_CMD_CMGW_PDU_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_WritePduMsgToMem: invalid command operation.");
        return AT_ERROR;
    }

    if (gastAtClientTab[ucIndex].AtSmsData.ucPduLen > ulLen)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: invalid tpdu data length.");
        return AT_ERROR;
    }

    pstWriteParm = At_GetWriteMsgMem();

    pstWriteParm->enWriteMode = MN_MSG_WRITE_MODE_INSERT;
    pstWriteParm->enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    pstWriteParm->enStatus = gastAtClientTab[ucIndex].AtSmsData.SmState;

    /*sca*/
    if (ulLen > gastAtClientTab[ucIndex].AtSmsData.ucPduLen)
    {
        ulRet = At_GetScaFromInputStr(pData, &pstWriteParm->stMsgInfo.stScAddr, &ulAddrLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: fail to get sca from user input.");
            return AT_ERROR;
        }

        if (ulLen != (gastAtClientTab[ucIndex].AtSmsData.ucPduLen + ulAddrLen))
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: the length of <pdu> is not consistent with <length>.");
            return AT_ERROR;
        }

    }

    if (0 == pstWriteParm->stMsgInfo.stScAddr.ucBcdLen)
    {
        if (0 == pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: without sca.");
        }
        else
        {
            PS_MEM_CPY(&pstWriteParm->stMsgInfo.stScAddr,
                       &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
                       sizeof(pstWriteParm->stMsgInfo.stScAddr));
        }
    }

    pstWriteParm->stMsgInfo.stTsRawData.ulLen = gastAtClientTab[ucIndex].AtSmsData.ucPduLen;
    PS_MEM_CPY(pstWriteParm->stMsgInfo.stTsRawData.aucData,
               &pData[ulAddrLen],
               gastAtClientTab[ucIndex].AtSmsData.ucPduLen);

    ucFo = pstWriteParm->stMsgInfo.stTsRawData.aucData[0];
    pstWriteParm->stMsgInfo.stTsRawData.enTpduType = aucMtiMapTpduType[(ucFo & 0x03)];;

    /*����PDU����Ч�Լ�飬ɾ�������ֶ�*/
    pstTsDataInfo = At_GetMsgMem();
    ulRet = MN_MSG_Decode(&pstWriteParm->stMsgInfo.stTsRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: Fail to decode.");
        return AT_ERROR;
    }

    pstRawData = At_GetLongMsgSegMem();
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    if(MN_ERR_NO_ERROR != ulRet)
    {
        AT_NORM_LOG("At_WritePduMsgToMem: fail to encode.");
    }
    else
    {
        if (pstRawData->ulLen != pstWriteParm->stMsgInfo.stTsRawData.ulLen)
        {
            AT_NORM_LOG1("At_WritePduMsgToMem: pstSendParm->stMsgInfo.stTsRawData.ulLen not match:",
                         pstWriteParm->stMsgInfo.stTsRawData.ulLen);
            AT_NORM_LOG1("At_WritePduMsgToMem: pstRawData->ulLen not match:", pstRawData->ulLen);
            pstWriteParm->stMsgInfo.stTsRawData.ulLen = pstRawData->ulLen;
        }

    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Write(gastAtClientTab[ucIndex].usClientId, opId, pstWriteParm);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : AT_ConvertCharToHex
 ��������  : ת�������ַ�������
 �������  : VOS_UINT8                           ucChar
             VOS_UINT8                          *pucHexValue
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_ConvertCharToHex(
    VOS_UINT8                           ucChar,
    VOS_UINT8                          *pucHexValue
)
{
    if( (ucChar >= '0') && (ucChar <= '9') )
    {
        *pucHexValue = ucChar - '0';
    }
    else if( (ucChar >= 'a') && (ucChar <= 'f') )
    {
        *pucHexValue = (ucChar - 'a') + 10;
    }
    else if( (ucChar >= 'A') && (ucChar <= 'F') )
    {
        *pucHexValue = (ucChar - 'A') + 10;
    }
    else
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_GetInvalidCharLengthForSms
 ��������  : ��ȡ����PDU����Ч�ַ��ĳ���
 �������  : VOS_UINT8                          *pucPdu PDU�����׵�ַ
             VOS_UINT32                          ulLen  PDU��������
             VOS_UINT32                         *pulInvalidCharLen  ��Ч�ַ�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_GetInvalidCharLengthForSms(
    VOS_UINT8                          *pucPdu,
    VOS_UINT32                          ulLen,
    VOS_UINT32                         *pulInvalidCharLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulInvalidCharLength;
    VOS_UINT8                           ucHex;

    ulInvalidCharLength = 0;
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        ulRet = AT_ConvertCharToHex(pucPdu[ulLoop], &ucHex);
        if (AT_FAILURE != ulRet)
        {
            break;
        }

        ulInvalidCharLength++;
    }

    *pulInvalidCharLength = ulInvalidCharLength;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ProcAbnormalPdu
 ��������  : PDU��ʽSMSģʽ��������ַ�������������CTRL+Z�쳣���봦��
 �������  : VOS_UINT8                          *pucPdu PDU�����׵�ַ
             VOS_UINT32                          ulLen  PDU��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��27��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012032205203,PDUģʽ�·����ţ�ESCȡ���󷵻�ERROR���ֲ᲻һ��
*****************************************************************************/
VOS_UINT32 AT_ProcAbnormalPdu(
    VOS_UINT8                          *pucPdu,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulInvalidCharLength;

    if (AT_ESC == pucPdu[ulLen])
    {
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }

    /* ����At_SmsPduProc������ֻ�н�����Ϊ�س�,CTRL+Z��ESC���������
       At_SmsPduProc�����ĵ�һ��CASE������CTRL+Z,������ǰ�����̴�����ESC���
       ��δ���������ַ���������Ϊ�س��Ĵ��� */
    AT_GetInvalidCharLengthForSms(pucPdu, ulLen, &ulInvalidCharLength);
    if (ulInvalidCharLength == ulLen)
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_CMS_INVALID_PDU_MODE_PARAMETER;
    }
}

/*****************************************************************************
 Prototype      : At_SmsPduProc
 Description    : ����PDU����
 Input          : ucIndex --- �û�����ֵ
                  pData   --- ��ַ
                  usLen   --- ����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2008��04��18��
    ��    �� : f62575
    �޸����� : CM�Ż�
  3.��    ��   : 2009��9��25��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ�ţ�AT2D14190�����ŷ���ʧ�ܴ���ԭ��ֵ���˲�һ��
*****************************************************************************/
TAF_UINT32 At_SmsPduProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    VOS_UINT32                          ulInvalidCharLength;
    TAF_UINT16                          usTmpLen            = usLen;
    TAF_UINT32                          ulRet;

    usTmpLen -= 1;              /* �ҵ����һ���ַ� */
    switch (pData[usTmpLen])    /* �������һ���ַ�������һ������ */
    {
    case AT_CTRL_Z:
        /* ���ݵ�ǰ�û�����������,����/д/PDU[����/����] */
        AT_GetInvalidCharLengthForSms(pData, usTmpLen, &ulInvalidCharLength);
        pData    += ulInvalidCharLength;
        usTmpLen -= (VOS_UINT16)ulInvalidCharLength;

        if(AT_FAILURE == At_UnicodePrint2Unicode(pData,&usTmpLen))
        {
            return AT_CMS_INVALID_PDU_MODE_PARAMETER;
        }

        switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
        case AT_CMD_CMGS_PDU_SET:
        case AT_CMD_CMGC_PDU_SET:
            ulRet = At_SendPduMsgOrCmd(ucIndex, pData, usTmpLen);
            break;

        case AT_CMD_CMGW_PDU_SET:
            ulRet = At_WritePduMsgToMem(ucIndex, pData, usTmpLen);
            break;

        case AT_CMD_CNMA_PDU_SET:
            ulRet = At_SendPduMsgAck(ucIndex, pData, usTmpLen);
            break;

        default:
            ulRet = AT_ERROR;                                                   /*  ���ش���*/
        }
        break;
    default:
        ulRet = AT_ProcAbnormalPdu(pData, usTmpLen);                            /*  ���ش���*/
        break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : At_SendTextMsgOrCmd
 ��������  : �ı�����Ϣ������ķ���
 �������  : ucIndex - �û�����ֵ
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2009-09-08
    ��    ��   : F62575
    �޸�����   : ���ⵥ��:����TE��MT���ַ�������ΪIRA�����ű�������Ϊ7BIT���룬���������ַ�@�ȶ������ݣ�д�뵽SIM���е����ݴ���
  3.��    ��   : 2009��9��25��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ�ţ�AT2D14190�����ŷ���ʧ�ܴ���ԭ��ֵ���˲�һ��
  4.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
  5.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
  6.��    ��   : 2011��03��01��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                 ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
  7.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
  8.��    ��   : 2013��12��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
TAF_UINT32  At_SendTextMsgOrCmd(
    TAF_UINT8                           ucIndex
)
{
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    TAF_UINT32                          ulRet;
    MN_MSG_SEND_PARM_STRU               *pstSendDirectParm;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    AT_MODEM_SMS_CTX_STRU               *pstSmsCtx = VOS_NULL_PTR;

    if ((AT_CMD_CMGS_TEXT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_CMGC_TEXT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        AT_WARN_LOG("At_SendTextMsgOrCmd: invalid command operation.");
        return AT_ERROR;
    }

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstTsDataInfo = At_GetMsgMem();
    pstSendDirectParm = At_GetDirectSendMsgMem();
    pstSendDirectParm->enDomain     = pstSmsCtx->stCgsmsSendDomain.enSendDomain;
    pstSendDirectParm->enMemStore   = MN_MSG_MEM_STORE_NONE;
    pstSendDirectParm->enClientType = MN_MSG_CLIENT_NORMAL;

    /*sc*/
    if (0 == pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen)
    {
        AT_NORM_LOG("At_SendTextMsgOrCmd: no SCA.");
        return AT_CMS_SMSC_ADDRESS_UNKNOWN;
    }
    PS_MEM_CPY(&pstSendDirectParm->stMsgInfo.stScAddr,
               &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
               sizeof(pstSendDirectParm->stMsgInfo.stScAddr));

    if (AT_CMD_CMGS_TEXT_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr��0,��MN�޸�*/

        /*Da*/
        PS_MEM_CPY(&pstTsDataInfo->u.stSubmit.stDestAddr,
                   &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                   sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stSubmit.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs,
                                 &pstTsDataInfo->u.stSubmit.stDcs);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            AT_NORM_LOG("At_SendTextMsgOrCmd: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*VP*/
        PS_MEM_CPY(&pstTsDataInfo->u.stSubmit.stValidPeriod,
                   &(pstSmsCtx->stCscaCsmpInfo.stVp),
                   sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));

        /*UDL UD*/
        if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_LEN)
        {
            AT_NORM_LOG("At_SendTextMsgOrCmd: invalid text message length.");
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

        pstTsDataInfo->u.stSubmit.stUserData.ulLen = gastAtClientTab[ucIndex].usSmsTxtLen;
        if ((AT_CSCS_IRA_CODE == gucAtCscsType)
         && (MN_MSG_MSG_CODING_7_BIT == pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding))
        {
            /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
            ulRet = TAF_STD_ConvertAsciiToDefAlpha(gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                                           gastAtClientTab[ucIndex].usSmsTxtLen,
                                           pstTsDataInfo->u.stSubmit.stUserData.aucOrgData);
            /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
            if (MN_ERR_INVALIDPARM == ulRet)
            {
                AT_NORM_LOG("At_SendTextMsgOrCmd: invalid text content.");
                return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
            }

        }
        else
        {
            PS_MEM_CPY(pstTsDataInfo->u.stSubmit.stUserData.aucOrgData,
                       gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                       pstTsDataInfo->u.stSubmit.stUserData.ulLen);
        }
    }
    else
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_COMMAND;
        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);
        /*Mr��0,��MN�޸�*/
        /*PID*/
        /*PID*/
        pstTsDataInfo->u.stCommand.enPid = gastAtClientTab[ucIndex].AtSmsData.enPid;

        /*TP-CT*/
        pstTsDataInfo->u.stCommand.enCmdType = gastAtClientTab[ucIndex].AtSmsData.CommandType;
        /*TP-MN*/ /* �˴�ȥ���˾��Ա������TAF_SMS_CMD_MSG_NUM_ABSOLUTE,��ȷ�� */
        pstTsDataInfo->u.stCommand.ucMsgNumber = gastAtClientTab[ucIndex].AtSmsData.ucMessageNumber;

        /*Da*/
        PS_MEM_CPY(&pstTsDataInfo->u.stCommand.stDestAddr,
                   &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                   sizeof(pstTsDataInfo->u.stCommand.stDestAddr));
        /*CDL CD*/
        if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_COMMAND_DATA_LEN)
        {
            AT_NORM_LOG("At_SendTextMsgOrCmd: invalid text command length.");
            return AT_ERROR;
        }

        /*����ʹ����gastAtClientTab[ucIndex].usSmsTxtLen��Ϊ����ȣ���ԭ����ͬ����ȷ��*/
        pstTsDataInfo->u.stCommand.ucCommandDataLen = (TAF_UINT8)gastAtClientTab[ucIndex].usSmsTxtLen;
        PS_MEM_CPY(pstTsDataInfo->u.stCommand.aucCmdData,
                   gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                   gastAtClientTab[ucIndex].usSmsTxtLen);
    }

    ulRet = MN_MSG_Encode(pstTsDataInfo, &pstSendDirectParm->stMsgInfo.stTsRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("At_SendTextMsgOrCmd: Fail to encode sms message or command.");
        return At_ChgMnErrCodeToAt(ucIndex, ulRet);
    }

    gastAtClientTab[ucIndex].opId = opId;
    ulRet = MN_MSG_Send(gastAtClientTab[ucIndex].usClientId,
                              gastAtClientTab[ucIndex].opId,
                              pstSendDirectParm);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_ERR_LOG("At_SendTextMsgOrCmd: Fail to send sms message or command.");
        if (MN_ERR_CLASS_SMS_NOAVAILDOMAIN == ulRet)
        {
            ulRet = AT_CMS_UNKNOWN_ERROR;
        }
        else
        {
            ulRet = AT_ERROR;
        }
    }
    else
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
    }
    return ulRet;
}

/*****************************************************************************
 �� �� ��  : At_WriteTextMsgToMem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���
  2.��    ��   : 2009-09-08
    ��    ��   : F62575
    �޸�����   : ���ⵥ��:����TE��MT���ַ�������ΪIRA�����ű�������Ϊ7BIT���룬���������ַ�@�ȶ������ݣ�д�뵽SIM���е����ݴ���
  3.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
  4.��    ��   : 2013��12��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
TAF_UINT32  At_WriteTextMsgToMem(
    TAF_UINT8                           ucIndex
)
{
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    TAF_UINT32                          ulRet;
    MN_MSG_WRITE_PARM_STRU              *pstWriteParm;
    MN_MSG_DCS_CODE_STRU                *pstDcs;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_CMD_CMGW_TEXT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_WriteTextMsgToMem: invalid command operation.");
        return AT_ERROR;
    }

    pstTsDataInfo = At_GetMsgMem();
    pstWriteParm = At_GetWriteMsgMem();
    pstWriteParm->enWriteMode = MN_MSG_WRITE_MODE_INSERT;
    pstWriteParm->enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    pstWriteParm->enStatus = gastAtClientTab[ucIndex].AtSmsData.SmState;

    if (0 == pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen)
    {
        AT_NORM_LOG("At_WriteTextMsgToMem: no SCA.");
        return AT_ERROR;
    }
    PS_MEM_CPY(&pstWriteParm->stMsgInfo.stScAddr,
               &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.stScAddr),
               sizeof(pstWriteParm->stMsgInfo.stScAddr));

    if ((MN_MSG_STATUS_MO_NOT_SENT == gastAtClientTab[ucIndex].AtSmsData.SmState)
     || (MN_MSG_STATUS_MO_SENT == gastAtClientTab[ucIndex].AtSmsData.SmState))
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_SUBMIT;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr��0,��MN�޸�*/
        pstTsDataInfo->u.stSubmit.ucMr = 0xff;

        /*Da*/
        PS_MEM_CPY(&pstTsDataInfo->u.stSubmit.stDestAddr,
                   &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                   sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stSubmit.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        pstDcs = &pstTsDataInfo->u.stSubmit.stDcs;
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs, pstDcs);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*VP*/
        PS_MEM_CPY(&pstTsDataInfo->u.stSubmit.stValidPeriod,
                   &(pstSmsCtx->stCscaCsmpInfo.stVp),
                   sizeof(pstTsDataInfo->u.stSubmit.stValidPeriod));

        /*UDL UD*/
        if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_7_BIT_LEN)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: invalid text message length.");
            return AT_ERROR;
        }

        pstTsDataInfo->u.stSubmit.stUserData.ulLen = gastAtClientTab[ucIndex].usSmsTxtLen;
        if ((AT_CSCS_IRA_CODE == gucAtCscsType)
         && (MN_MSG_MSG_CODING_7_BIT == pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding))
        {
            /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
            ulRet = TAF_STD_ConvertAsciiToDefAlpha(gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                                           gastAtClientTab[ucIndex].usSmsTxtLen,
                                           pstTsDataInfo->u.stSubmit.stUserData.aucOrgData);
            /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
            if (MN_ERR_INVALIDPARM == ulRet)
            {
                AT_NORM_LOG("At_WriteTextMsgToMem: invalid text content.");
                return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
            }
        }
        else
        {
            PS_MEM_CPY(pstTsDataInfo->u.stSubmit.stUserData.aucOrgData,
                       gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                       gastAtClientTab[ucIndex].usSmsTxtLen);
        }

    }
    else
    {
        pstTsDataInfo->enTpduType = MN_MSG_TPDU_DELIVER;

        /*Fo*/
        At_SendMsgFoAttr(ucIndex, pstTsDataInfo);

        /*Mr��0,��MN�޸�*/

        /*Da*/
        PS_MEM_CPY(&pstTsDataInfo->u.stDeliver.stOrigAddr,
                   &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                   sizeof(pstTsDataInfo->u.stSubmit.stDestAddr));

        /*PID*/
        pstTsDataInfo->u.stDeliver.enPid = pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid;

        /*DCS*/
        pstDcs = &pstTsDataInfo->u.stDeliver.stDcs;
        ulRet = MN_MSG_DecodeDcs(pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs, pstDcs);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: Fail to decode DCS.");
            return AT_ERROR;
        }

        /*SCTS??*/

        /*UDL UD*/
        if (gastAtClientTab[ucIndex].usSmsTxtLen > MN_MSG_MAX_7_BIT_LEN)
        {
            AT_NORM_LOG("At_WriteTextMsgToMem: invalid text message length.");
            return AT_ERROR;
        }
        pstTsDataInfo->u.stDeliver.stUserData.ulLen = gastAtClientTab[ucIndex].usSmsTxtLen;
        if ((AT_CSCS_IRA_CODE == gucAtCscsType)
         && (MN_MSG_MSG_CODING_7_BIT == pstTsDataInfo->u.stSubmit.stDcs.enMsgCoding))
        {
            ulRet = TAF_STD_ConvertAsciiToDefAlpha(gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                                           gastAtClientTab[ucIndex].usSmsTxtLen,
                                           pstTsDataInfo->u.stDeliver.stUserData.aucOrgData);
            if (MN_ERR_INVALIDPARM == ulRet)
            {
                AT_NORM_LOG("At_WriteTextMsgToMem: invalid text content.");
                return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
            }
        }
        else
        {
            PS_MEM_CPY(pstTsDataInfo->u.stDeliver.stUserData.aucOrgData,
                       gastAtClientTab[ucIndex].AtSmsData.aucBuffer,
                       gastAtClientTab[ucIndex].usSmsTxtLen);
        }

    }

    ulRet = MN_MSG_Encode(pstTsDataInfo, &pstWriteParm->stMsgInfo.stTsRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("At_WriteTextMsgToMem: Fail to encode sms message or command.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_Write(gastAtClientTab[ucIndex].usClientId,
                         gastAtClientTab[ucIndex].opId,
                         pstWriteParm);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        ulRet = AT_ERROR;
    }
    else
    {
        ulRet = AT_WAIT_ASYNC_RETURN;
    }
    return ulRet;
}

/*****************************************************************************
 Prototype      : At_SmsTextProc
 Description    : ����TEXT����
 Input          : ucIndex --- �û�����ֵ
                  pData   --- ��ַ
                  usLen   --- ����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)

 3.��    �� : 2007-09-24
   ��    �� : z40661
   �޸����� : ���ⵥ��:A32D12776
 4.��    �� : 2008��04��18��
   ��    �� : f62575
   �޸����� : CM�Ż�
 5.��    ��   : 2009��9��25��
   ��    ��   : fuyingjun
   �޸�����   : ���ⵥ�ţ�AT2D14190�����ŷ���ʧ�ܴ���ԭ��ֵ���˲�һ��
 6.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
*****************************************************************************/
TAF_UINT32 At_SmsTextProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    TAF_UINT16                          usTmpLen            = usLen;
    TAF_UINT8                           ucSmsProcType       = 0;
    TAF_UINT32                          ulRet;

    if(AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        usTmpLen -= 1;
        if(AT_CTRL_Z == pData[usTmpLen])
        {
            ucSmsProcType = 1;
        }
        else if(ucAtS3 == pData[usTmpLen])
        {
            ucSmsProcType = 2;
        }
        else
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
        if(AT_FAILURE == At_UnicodePrint2Unicode(pData,&usTmpLen))
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

        /* UNICODE �����ж� */
        if ((gastAtClientTab[ucIndex].usSmsTxtLen + usTmpLen) > AT_UNICODE_SMS_MAX_LENGTH)
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
    }
    else
    {
        if(AT_CTRL_Z == pData[usTmpLen - 1])
        {
            usTmpLen -= 1;
            ucSmsProcType = 1;
        }
        else if(ucAtS3 == pData[usTmpLen - 1])
        {
            ucSmsProcType = 2;
        }
        else
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }

        /* ASCII �����ж� */
        if ((gastAtClientTab[ucIndex].usSmsTxtLen + usTmpLen) > AT_ASCII_SMS_MAX_LENGTH)
        {
            return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
        }
    }

    switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
    case AT_CMD_CMGS_TEXT_SET:
    case AT_CMD_CMGW_TEXT_SET:
    case AT_CMD_CMGC_TEXT_SET:
        PS_MEM_CPY(&gastAtClientTab[ucIndex].AtSmsData.aucBuffer[gastAtClientTab[ucIndex].usSmsTxtLen],
                  pData,
                  usTmpLen);
        break;

    default:
        return AT_ERROR;
    }
    gastAtClientTab[ucIndex].usSmsTxtLen += usTmpLen;
    if (1 == ucSmsProcType)
    {
        switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
        case AT_CMD_CMGS_TEXT_SET:
        case AT_CMD_CMGC_TEXT_SET:
            ulRet = At_SendTextMsgOrCmd(ucIndex);
            break;
        default:
            ulRet = At_WriteTextMsgToMem(ucIndex);
            break;
        }

    }
    else
    {
        /* ���������Ż���,�޸Ķ����ı����� */
        ulRet = AT_WAIT_SMS_INPUT;
    }
    return ulRet;
}
/*****************************************************************************
 Prototype      : At_SmsProc
 Description    : ���Ŵ���
 Input          : ucIndex --- �û�����ֵ
                  pData   --- ��ַ
                  usLen   --- ����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2008��04��18��
    ��    �� : f62575
    �޸����� : CM�Ż�
  3.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SmsProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ��ȡ��ǰ����ģʽ */
    if (AT_CMGF_MSG_FORMAT_TEXT == pstSmsCtx->enCmgfMsgFormat)                  /* TEXT */
    {
        return At_SmsTextProc(ucIndex,pData,usLen);
    }
    else
    {
        /* ������������⣬����AT_ERROR */
        return At_SmsPduProc(ucIndex,pData,usLen);                              /* PDU */
    }
}


/*****************************************************************************
 �� �� ��  : At_ParseSimLockPara
 ��������  : �� AT �ַ���������AT_Pase�ĸ���
 �������  : pucData -- simlock���������
             usLen -- �������ַ�������
             pstParalist -- ���������Ĳ����б�
             ulParaCnt-- ��������  = �����ַ����ж��Ÿ��� + 1
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��13��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_ParseSimLockPara(
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist,
    VOS_UINT32                          ulParaCnt
)
{
    VOS_UINT8                           *pucParaStart;
    VOS_UINT32                          ulParaIdx;
    VOS_UINT32                          ulChkRslt;
    VOS_UINT32                          i;

    if (VOS_NULL_PTR == pstParalist)
    {
        AT_ERR_LOG("At_PareseSimLockPara: pstParalist = VOS_NULL_PTR!");
        return AT_FAILURE;
    }

    pucParaStart  = pucData;
    ulParaIdx     = 0;

    /* ��AT^simlock=pucData��pucData��ʼ����  */
    for ( i = 0; i < usLen ; i++ )
    {
        if (',' == pucData[i])
        {
            /* ��ǰ�����ĳ��� */
            ulChkRslt = At_CheckAndParsePara((pstParalist + ulParaIdx),
                                                   pucParaStart, (pucData + i));
            if (AT_OK != ulChkRslt)
            {
                return AT_FAILURE;
            }

            pucParaStart = (pucData + i) + 1;
            ++ ulParaIdx;

            if (ulParaIdx >= ulParaCnt)
            {
                return AT_FAILURE;
            }
        }

    }

    /*  �����һ�β����޸�copy�������б��� */
    ulChkRslt = At_CheckAndParsePara((pstParalist + ulParaIdx),
                                           pucParaStart, (pucData + usLen));
    if (AT_OK != ulChkRslt)
    {
        return AT_FAILURE;
    }

    ++ ulParaIdx;

    if (ulParaIdx > ulParaCnt)
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;

}
/*****************************************************************************
 �� �� ��  : At_DispatchSimlockCmd
 ��������  : ����at^simlock=oprt,paralist�е�oprt�ַ� Simlock�������
 �������  : SimlockOp
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��14��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��3��
    ��    ��   : f62575
    �޸�����   : B050 SIMLOCK�����Ӳ���ܸ��ƹ���: SIMLOCK����״̬��ѯ���ܷ�װΪ����

*****************************************************************************/
VOS_UINT32 At_DispatchSimlockCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
)
{
    VOS_UINT8                           ucSimLockOP;

    if ((ulParaCnt < 1) || (VOS_NULL_PTR == pstParalist))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_FAILURE;
    }

    if ((1 != pstParalist[0].usParaLen)
     || (pstParalist[0].aucPara[0] <'0')
     || (pstParalist[0].aucPara[0] > '2'))
    {
        /*�������*/
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_FAILURE;
    }

    ucSimLockOP = pstParalist[0].aucPara[0] - '0';

    if (AT_SIMLOCK_OPRT_UNLOCK == ucSimLockOP)
    {
        At_UnlockSimLock(ucIndex, ulParaCnt,pstParalist);
    }
    else if (AT_SIMLOCK_OPRT_SET_PLMN_INFO == ucSimLockOP)
    {
        At_SetSimLockPlmnInfo(ucIndex, ulParaCnt,pstParalist);
    }
    else
    {
        AT_GetSimLockStatus(ucIndex);
    }
    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : At_ProcSimLockPara
 ��������  : ����Simlock����
 �������  : ucIndex --- �û�����
             pucData --- ������ַ���
             pusLen --- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��Simlock����,�������
             AT_FAILURE ����Simlock����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��10��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort, ƥ��ͼ�¼AT������
*****************************************************************************/
VOS_UINT32 At_ProcSimLockPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdLen;
    VOS_UINT8                           *pucDataPara = TAF_NULL_PTR;
    VOS_UINT32                          ulParaCnt;
    AT_PARSE_PARA_TYPE_STRU             *pstParalist;
    VOS_UINT32                          ulRslt;

    if (0 == usLen)
    {
        return AT_FAILURE;
    }

    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    if (VOS_NULL_PTR == pucDataPara)
    {
        AT_ERR_LOG("At_ProcSimLockPara: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    PS_MEM_CPY(pucDataPara, pucData, usLen);


    /* ��������ַ�������С�ڵ���"AT^SIMLOCK"����ֱ�ӷ���AT_FAILURE */
    usCmdLen =(VOS_UINT16)VOS_StrLen("AT^SIMLOCK=");

    if (usLen <= usCmdLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* ��������ַ���ͷ������"AT^SIMLOCK"ֱ�ӷ���AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^SIMLOCK=", usCmdLen);

    if (0 != cRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^SIMLOCK", AT_EXTEND_CMD_TYPE);

    /* ���������� */
    ulParaCnt = At_GetParaCnt(pucDataPara, usLen);

    if (ulParaCnt < 1)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }

    /* ��������ǳ���61������ʧ�� */
    if (ulParaCnt > 61)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_SIMLOCK_PLMN_NUM_ERR);
        return AT_SUCCESS;
    }

    pstParalist = (AT_PARSE_PARA_TYPE_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT,
                                (ulParaCnt * sizeof(AT_PARSE_PARA_TYPE_STRU)));

    if (VOS_NULL_PTR == pstParalist)
    {
        AT_ERR_LOG("At_ProcSimLockPara: pstParalist Memory malloc failed!");
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }
    else
    {
        PS_MEM_SET(pstParalist, 0x00, (VOS_SIZE_T)(ulParaCnt * sizeof(AT_PARSE_PARA_TYPE_STRU)));
    }

    /* �� At^simlock�Ĳ��������� At��ʽ�Ĳ����б��� */
    ulRslt = At_ParseSimLockPara((pucDataPara + usCmdLen), (usLen - usCmdLen),
                                                    pstParalist, ulParaCnt);

    if (AT_SUCCESS == ulRslt)
    {
        /* ����at^simlock=oprt,paralist�е�oprt�ַ� Simlock������� */
        At_DispatchSimlockCmd(ucIndex, ulParaCnt, pstParalist);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    PS_MEM_FREE(WUEPS_PID_AT,pstParalist);
    PS_MEM_FREE(WUEPS_PID_AT,pucDataPara);

    return AT_SUCCESS;

}

/*****************************************************************************
 �� �� ��  : AT_HandleFacAuthPubKeyCmd
 ��������  : ����AT^FACAUTHPUBKEY��������⺯��(��Ϊ������ĵ�һ���������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex --- �û�����
             pucData --- ������ַ���
             pusLen --- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^FACAUTHPUBKEY����,�������
             AT_FAILURE ����^FACAUTHPUBKEY����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��18��
    ��    ��   : L47619
    �޸�����   : AP-Modem����������Ŀ��������

  2.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort, ����������Ϣ, AT��ϴ�����Ҫʹ��
  3.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_HandleFacAuthPubKeyCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT8                          *pucDataPara;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    AT_FACAUTHPUBKEY_SET_REQ_STRU      *pstFacAuthPubKey;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT32                          ulResult;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;

    PS_MEM_SET(&stAtCmdName, 0, sizeof(stAtCmdName));

    /* �ֲ�������ʼ�� */
    usPos               = 0;
    pucDataPara         = VOS_NULL_PTR;
    usLoop              = 0;
    usCommaCnt          = 0;
    usFirstCommaPos     = 0;
    pstFacAuthPubKey    = VOS_NULL_PTR;
    usFirstParaLen      = 0;
    usSecondParaLen     = 0;

    /* Ϊ���AT�������ܣ�����ڴ��ж�������Ƿ�ΪAT^FACAUTHPUBKEY��������ĳ��ȣ���������ֱ���˳� */
    if ((VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN) != usLen)
    {
        return AT_FAILURE;
    }

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^FACAUTHPUBKEY=");

    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usCmdlen);
    if (VOS_NULL_PTR == pucDataPara)
    {
        AT_ERR_LOG("AT_HandleFacAuthPubKeyCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    /*�������������������Ƚ�ʹ��*/
    PS_MEM_CPY(pucDataPara, pucData, usCmdlen);

    /* AT����ͷ�ַ�ת��д */
    At_UpString(pucDataPara, usCmdlen);

    /* ��������ַ���ͷ������"AT^FACAUTHPUBKEY="ֱ�ӷ���AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^FACAUTHPUBKEY=", usCmdlen);
    if (0 != cRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^FACAUTHPUBKEY", AT_EXTEND_CMD_TYPE);

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    usPos = (VOS_UINT16)VOS_StrLen("AT");
    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^FACAUTHPUBKEY");
    PS_MEM_CPY(stAtCmdName.aucCmdName,
               (pucData + usPos),
               stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    usPos += stAtCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ��ȡ�����еĶ���λ�ú͸��� */
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (',' == *(pucData + usLoop))
        {
            usCommaCnt++;
            /* ��¼�µ�һ�����ŵ�λ�� */
            if (0 == usFirstCommaPos)
            {
                usFirstCommaPos = usLoop + 1;
            }
        }
    }

    /* �����Ÿ�����Ϊ1����AT����������ʧ�� */
    if (1 != usCommaCnt)
    {
        AT_WARN_LOG("AT_HandleFacAuthPubKeyCmd: usCommaCnt != 1!");
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);
        return AT_SUCCESS;
    }

    /* �������������ĳ��� */
    usFirstParaLen  = (usFirstCommaPos - usPos) - 1;
    usSecondParaLen = usLen - usFirstCommaPos;

    /* �������Ȳ���ȷ����AT����������ʧ�� */
    if ((AT_FACAUTHPUBKEY_PARA_LEN != usFirstParaLen )
     || (AT_FACAUTHPUBKEY_SIGN_PARA_LEN != usSecondParaLen))
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);
        return AT_SUCCESS;
    }

    /* ���������������ṹ */
    pstFacAuthPubKey = (AT_FACAUTHPUBKEY_SET_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_FACAUTHPUBKEY_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstFacAuthPubKey)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_ERROR);
        AT_ERR_LOG("AT_HandleFacAuthPubKeyCmd: pstFacAuthPubKey Memory malloc failed!");
        return AT_SUCCESS;
    }

    /* �����һ������ */
    PS_MEM_CPY(pstFacAuthPubKey->aucPubKey, pucData + usPos, usFirstParaLen);

    /* ����ڶ������� */
    PS_MEM_CPY(pstFacAuthPubKey->aucPubKeySign, pucData + usFirstCommaPos, usSecondParaLen);

    /* �����������ͣ��������ͺͲ������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    ulResult = AT_SetFacAuthPubkeyPara(ucIndex, pstFacAuthPubKey);
    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }
    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    PS_MEM_FREE(WUEPS_PID_AT, pstFacAuthPubKey);
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_HandleSimLockDataWriteCmd
 ��������  : ����AT^SIMLOCKDATAWRITE��������⺯��(��Ϊ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex --- �û�����
             pucData --- ������ַ���
             pusLen --- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^SIMLOCKDATAWRITE����,�������
             AT_FAILURE ����^SIMLOCKDATAWRITE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��18��
    ��    ��   : L47619
    �޸�����   : AP-Modem����������Ŀ��������
  2.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort, ����������Ϣ, AT��ϴ�����Ҫʹ��
  3.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_HandleSimLockDataWriteCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT8                          *pucDataPara;
    AT_SIMLOCKDATAWRITE_SET_REQ_STRU   *pstSimlockDataWrite;
    VOS_UINT32                          ulResult;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;

    PS_MEM_SET(&stAtCmdName, 0, sizeof(stAtCmdName));

    /* �ֲ�������ʼ�� */
    pucDataPara         = VOS_NULL_PTR;
    pstSimlockDataWrite = VOS_NULL_PTR;

    /* Ϊ���AT�������ܣ�����ڴ��ж�������Ƿ�ΪAT^SIMLOCKDATAWRITE��������ĳ��ȣ���������ֱ���˳� */
    if ((VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN) != usLen)
    {
        return AT_FAILURE;
    }

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^SIMLOCKDATAWRITE=");

    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usCmdlen);
    if (VOS_NULL_PTR == pucDataPara)
    {
        AT_ERR_LOG("AT_HandleSimLockDataWriteCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    /*�������������������Ƚ�ʹ��*/
    PS_MEM_CPY(pucDataPara, pucData, usCmdlen);

    /* AT����ͷ�ַ�ת��д */
    At_UpString(pucDataPara, usCmdlen);

    /* ��������ַ���ͷ������"AT^SIMLOCKDATAWRITE="ֱ�ӷ���AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^SIMLOCKDATAWRITE=", usCmdlen);
    if (0 != cRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^SIMLOCKDATAWRITE", AT_EXTEND_CMD_TYPE);

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    usPos = (VOS_UINT16)VOS_StrLen("AT");
    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^SIMLOCKDATAWRITE");
    PS_MEM_CPY(stAtCmdName.aucCmdName,
               (pucData + usPos),
               stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    usPos += stAtCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ���������������ṹ */
    pstSimlockDataWrite = (AT_SIMLOCKDATAWRITE_SET_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_SIMLOCKDATAWRITE_SET_REQ_STRU));
    if (VOS_NULL_PTR == pstSimlockDataWrite)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_SUCCESS;
    }

    /* ������� */
    PS_MEM_CPY(pstSimlockDataWrite->aucCategoryData, (pucData + usPos), (VOS_SIZE_T)(usLen - usPos));

    /* �����������ͣ��������ͺͲ������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    ulResult = AT_SetSimlockDataWritePara(ucIndex, pstSimlockDataWrite);
    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }
    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    PS_MEM_FREE(WUEPS_PID_AT, pstSimlockDataWrite);
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_HandleApSndApduCmd
 ��������  : ����AT^CISA��������⺯��(��Ϊ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex    -- �û�����
             pucData    -- ������ַ���
             pusLen     -- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^CISA����,�������
             AT_FAILURE ����^CISA����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��01��
    ��    ��   : H59254
    �޸�����   : ISDB��ȫ�洢��Ŀ��������
*****************************************************************************/
VOS_UINT32 AT_HandleApSndApduCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    /* CISA����ֻ�ܴ�AP����մ��������˿ڲ����� */
    if (VOS_TRUE != AT_IsApPort(ucIndex))
    {
        return AT_FAILURE;
    }

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CISA=");

    /* ��������ַ���ͷ������"AT^CISA="ֱ�ӷ���AT_FAILURE */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CISA=", usCmdlen))
    {
        return AT_FAILURE;
    }

    /* ��֧��AT^CISA=?���� */
    if (0 == VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CISA=?", VOS_StrLen("AT^CISA=?")))
    {
        At_FormatResultData(ucIndex, AT_ERROR);

        return AT_SUCCESS;
    }

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CISA");

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName,
               (pucData + usPos),
               g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ��ȡ�����еĶ���λ�ú͸��� */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (',' == *(pucData + usLoop))
        {
            usCommaCnt++;

            /* ��¼�µ�һ�����ŵ�λ�� */
            if (0 == usFirstCommaPos)
            {
                usFirstCommaPos = usLoop + 1;
            }
        }
    }

    /* �����Ÿ�����Ϊ1����AT����������ʧ�� */
    if (1 != usCommaCnt)
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �ڶ��������������Ű��������� */
    ucHeadChar      = *(pucData + usFirstCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( ('"' != ucHeadChar)
      || ('"' != ucTailChar) )
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: <command> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �������������ĳ��� */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usLen - usFirstCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    if (AT_FAILURE == atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue))
    {
        AT_WARN_LOG("AT_HandleApSndApduCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }
    /* �����������ͣ��������ͺͲ������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ����չ�������ƥ������� */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if(ERR_MSP_SUCCESS != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCISAPara(ucIndex,
                              ulLengthValue,
                              (pucData + usFirstCommaPos + VOS_StrLen("\"")),
                              usSecondParaLen);

    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AT_HandleApSecCmd
 ��������  : ����AT^APSEC��������⺯��(��Ϊ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex    -- �û�����
             pucData    -- ������ַ���
             pusLen     -- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^APSEC����,�������
             AT_FAILURE ����^APSEC����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��  : 2012��08��28��
    ��    ��  : l00198894
    �޸�����  : ISDB ��ȫ�洢��Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_HandleApSecCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usParaLen;
    VOS_UINT16                          usCmdLen;
    VOS_UINT8                          *pucCmdPara;
    VOS_INT8                            cRet;

    /* ͨ�����, ��ָ��ͨ���·������������ERROR */
    if (AT_MUX4_USER != gastAtClientTab[ucIndex].UserType)
    {
        return AT_FAILURE;
    }

    /* �ж������ */
    if ( (AT_APSEC_CMD_MAX_LEN < usLen)
      || (AT_APSEC_CMD_MIN_LEN > usLen) )
    {
        return AT_FAILURE;
    }

    /* �ж������Ƿ���"AT^APSEC="��ͷ */
    usCmdLen        = (VOS_UINT16)VOS_StrLen("AT^APSEC=");
    cRet            = VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^APSEC=", usCmdLen);
    if (0 != cRet)
    {
        return AT_FAILURE;
    }

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^APSEC");
    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName,
               "^APSEC",
               g_stATParseCmd.stCmdName.usCmdNameLen);
    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    /* �����������ͣ��������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    g_stATParseCmd.ucCmdFmtType = AT_EXTEND_CMD_TYPE;

    /* ���������ƥ������� */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if(ERR_MSP_SUCCESS != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
        return AT_SUCCESS;
    }

    /* ����������� */
    usParaLen       = usLen - usCmdLen;
    pucCmdPara      = pucData + usCmdLen;
    ulResult        = AT_SetApSecPara(ucIndex, pucCmdPara, usParaLen);
    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AT_HandleApXsmsSndCmd
 ��������  : ����AT^CCMGS��������⺯��(��Ϊ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex    -- �û�����
             pucData    -- ������ַ���
             pusLen     -- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^CCMGS����,�������
             AT_FAILURE ����^CCMGS����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��30��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_HandleApXsmsSndCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CCMGS=");

    /* ��������ַ���ͷ������"AT^CCMGS="ֱ�ӷ���AT_FAILURE */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGS=", usCmdlen))
    {
        return AT_FAILURE;
    }

    /* ��֧��AT^CCMGS=?���� */
    if (0 == VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGS=?", VOS_StrLen("AT^CCMGS=?")))
    {
        At_FormatResultData(ucIndex, AT_OK);

        return AT_SUCCESS;
    }

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CCMGS");

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName,
               (pucData + usPos),
               g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ��ȡ�����еĶ���λ�ú͸��� */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (',' == *(pucData + usLoop))
        {
            usCommaCnt++;

            /* ��¼�µ�һ�����ŵ�λ�� */
            if (0 == usFirstCommaPos)
            {
                usFirstCommaPos = usLoop + 1;
            }
        }
    }

    /* �����Ÿ�����Ϊ1����AT����������ʧ�� */
    if (1 != usCommaCnt)
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �ڶ��������������Ű��������� */
    ucHeadChar      = *(pucData + usFirstCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( ('"' != ucHeadChar)
      || ('"' != ucTailChar) )
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <PDU> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �������������ĳ��� */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usLen - usFirstCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    if (AT_FAILURE == atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue))
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }
    /* �����������ͣ��������ͺͲ������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ����չ�������ƥ������� */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if (ERR_MSP_SUCCESS != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCcmgsPara(ucIndex,
                               ulLengthValue,
                               (pucData + usFirstCommaPos + VOS_StrLen("\"")),
                               usSecondParaLen);

    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_HandleApXsmsWriteCmd
 ��������  : ����AT^CCMGW��������⺯��(��Ϊ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex    -- �û�����
             pucData    -- ������ַ���
             pusLen     -- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��^CCMGS����,�������
             AT_FAILURE ����^CCMGS����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��30��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_HandleApXsmsWriteCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          usCmdlen;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usLoop;
    VOS_UINT16                          usCommaCnt;
    VOS_UINT16                          usFirstCommaPos;
    VOS_UINT16                          usSecondCommaPos;
    VOS_UINT16                          usFirstParaLen;
    VOS_UINT16                          usSecondParaLen;
    VOS_UINT16                          usThirdParaLen;
    VOS_UINT32                          ulLengthValue;
    VOS_UINT32                          ulStatValue;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucHeadChar;
    VOS_UINT8                           ucTailChar;

    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^CCMGW=");

    /* ��������ַ���ͷ������"AT^CCMGW="ֱ�ӷ���AT_FAILURE */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGW=", usCmdlen))
    {
        return AT_FAILURE;
    }

    /* ��֧��AT^CCMGS=?���� */
    if (0 == VOS_StrNiCmp((VOS_CHAR *)pucData, "AT^CCMGW=?", VOS_StrLen("AT^CCMGW=?")))
    {
        At_FormatResultData(ucIndex, AT_OK);

        return AT_SUCCESS;
    }

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    usPos = (VOS_UINT16)VOS_StrLen("AT");

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^CCMGW");

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName,
               (pucData + usPos),
               g_stATParseCmd.stCmdName.usCmdNameLen);

    g_stATParseCmd.stCmdName.aucCmdName[g_stATParseCmd.stCmdName.usCmdNameLen] = '\0';

    usPos += g_stATParseCmd.stCmdName.usCmdNameLen;

    usPos += (VOS_UINT16)VOS_StrLen("=");

    /* ��ȡ�����еĶ���λ�ú͸��� */
    usCommaCnt      = 0;
    usFirstCommaPos = 0;
    usSecondCommaPos= 0;

    for ( usLoop = usPos; usLoop < usLen; usLoop++ )
    {
        if (',' == *(pucData + usLoop))
        {
            usCommaCnt++;

            /* ��¼�µ�һ�����ŵ�λ�� */
            if (0 == usFirstCommaPos)
            {
                usFirstCommaPos = usLoop + 1;
            }

            /* ��¼�µڶ������ŵ�λ�� */
            if ((0 == usSecondCommaPos)
                && (2 == usCommaCnt))
            {
                usSecondCommaPos = usLoop + 1;
            }
        }
    }

    /* �����Ÿ�����Ϊ2����AT����������ʧ�� */
    if (2 != usCommaCnt)
    {
        AT_WARN_LOG("AT_HandleApXsmsWriteCmd: usCommaCnt != 1!");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �����������������Ű��������� */
    ucHeadChar      = *(pucData + usSecondCommaPos);
    ucTailChar      = *(pucData + usLen - VOS_StrLen("\""));
    if ( ('"' != ucHeadChar)
      || ('"' != ucTailChar) )
    {
        AT_WARN_LOG("AT_HandleApXsmsWriteCmd: <PDU> not a string");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �������������ĳ��� */
    usFirstParaLen  = (usFirstCommaPos - usPos) - (VOS_UINT16)VOS_StrLen(",");
    usSecondParaLen = usSecondCommaPos - usFirstCommaPos - (VOS_UINT16)VOS_StrLen(",");
    usThirdParaLen  = usLen - usSecondCommaPos - (VOS_UINT16)(2 * VOS_StrLen("\""));

    /* ��������1<len>��ֵ */
    if (AT_FAILURE == atAuc2ul(pucData + usCmdlen, usFirstParaLen, &ulLengthValue))
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* ��������2<stat>��ֵ */
    if (AT_FAILURE == atAuc2ul(pucData + usFirstCommaPos,
                               usSecondParaLen,
                               &ulStatValue))
    {
        AT_WARN_LOG("AT_HandleApXsmsSndCmd: <length> value invalid");

        At_FormatResultData(ucIndex, AT_CME_INCORRECT_PARAMETERS);

        return AT_SUCCESS;
    }

    /* �����������ͣ��������ͺͲ������� */
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType             = AT_EXTEND_CMD_TYPE;

    /* ����չ�������ƥ������� */
    ulResult = atMatchCmdName(ucIndex, g_stATParseCmd.ucCmdFmtType);

    if (ERR_MSP_SUCCESS != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);

        return AT_SUCCESS;
    }

    ulResult = AT_SetCcmgwPara(ucIndex,
                               ulLengthValue,
                               ulStatValue,
                               (pucData + usSecondCommaPos + VOS_StrLen("\"")),
                               usThirdParaLen);

    if (AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : At_HandleApModemSpecialCmd
 ��������  : ����AP-MODEM����������(��ΪAP-MODEM��ĳЩװ������Ĳ������ȳ���
             �������������ޣ���Ҫ�������⴦��)
 �������  : ucIndex --- �û�����
             pucData --- ������ַ���
             pusLen --- �ַ�������
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ��AP-MODEM����������,�������
             AT_FAILURE ����AP-MODEM����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��21��
    ��    ��   : L47619
    �޸�����   : AP-Modem����������Ŀ��������

  2.��    ��   : 2012��09��08��
    ��    ��   : l00198894
    �޸�����   : ISDB ��ȫ�洢��Ŀ��������AT��������⴦��

*****************************************************************************/
VOS_UINT32 At_HandleApModemSpecialCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                          *pucSystemAppConfig;

    /* ��ȡ��ǰ��Ʒ��̬ */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_FAILURE;
    }

    /* ����AT^FACAUTHPUBKEY=<pubkey>,<signature>��������(����<pubkey>����) */
    if (AT_SUCCESS == AT_HandleFacAuthPubKeyCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }

    /* ����AT^SIMLOCKDATAWRITE=<simlock_data_write>��������(����<simlock_data_write>����) */
    if (AT_SUCCESS == AT_HandleSimLockDataWriteCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }

    /* ����AT^CISA=<length>,<command> */
    if (AT_SUCCESS == AT_HandleApSndApduCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }

    /* ����AT^APSEC=<SP_request>��������(����<SP_request>����) */
    if (AT_SUCCESS == AT_HandleApSecCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }


    if (AT_SUCCESS == AT_HandleApXsmsSndCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }

    if (AT_SUCCESS == AT_HandleApXsmsWriteCmd(ucIndex, pucData, usLen))
    {
        return AT_SUCCESS;
    }


    /* ɾ����^EOPLMN���������������� */

    return AT_FAILURE;
}

/*****************************************************************************
 �� �� ��  : At_CheckUsimStatus
 ��������  : ��鵱ǰ��״̬
 �������  : TAF_UINT8* pucCmdName
 �������  : ��
 �� �� ֵ  : TAF_UINT32 �����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��16��
    ��    ��   : ŷ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��11��16��
    ��    ��   : ŷ����
    �޸�����   : DTS2010111503638������������ڣ��ϱ����󿨲����ڶ�����SIM
                 FAILURE
  3.��    ��   : 2010��11��16��
    ��    ��   : ŷ����
    �޸�����   : DTS2010120901306��CBC��ѯ����AT�����Ҫ��ѯ��״̬
  4.��    ��   : 2011��2��21��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011021000325��PIN�뿪����VODAFONE��̨���Ͷ���ʧ��
  5.��    ��   : 2011��08��15��
    ��    ��   : f00179208
    �޸�����   : DTS2011081400488��AT^CSNRӦ������PIN�룬���ڽ�PINǰ��ATδ��Ч
  6.��    ��   : 2011��10��10��
    ��    ��   : �޾�ǿ/c64416
    �޸�����   : �·����ɱ�־λ�ж��Ƿ���Ҫ���PIN��״̬
  7.��    ��   : 2011��10��27��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ͬ����״̬�жϣ�����At_CheckUsimStatus=>ȫ�ֱ���g_stAtUsimStatusCtx.enCardStatus
  8.��    ��   : 2012��03��06��
    ��    ��   : l00130025
    �޸�����   : DTS2012022501847:MP���·�����,Simδ�ϱ���״̬ʱ��
                  CLCK��ѯ���� 10:Sim not insert������MP��Ϊ����Ч,��Ҫ�޸ķ���Sim Busy
  9.��    ��   : 2012��12��24��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II
  10.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
  11.��    ��   : 2013��05��17��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
TAF_UINT32 At_CheckUsimStatus (
    TAF_UINT8                          *pucCmdName,
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stQuickStartFlg;

    stQuickStartFlg.ulQuickStartSta = AT_QUICK_START_DISABLE;
    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_CheckUsimStatus:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstSmsCtx      = AT_GetModemSmsCtxAddrFromModemId(enModemId);
    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);




    /* ���ٿ���ģʽ������� PIN ״̬ */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_FollowOn_OpenSpeed_Flag, (VOS_VOID*)(&stQuickStartFlg), sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
       stQuickStartFlg.ulQuickStartSta = AT_QUICK_START_DISABLE;
    }

    if(AT_QUICK_START_ENABLE == stQuickStartFlg.ulQuickStartSta)
    {
        return AT_SUCCESS;
    }

    /*SMS����������������Ҫ��ҵ��ģ���ڲ������˴�������CMGL����������Ĵ����ȷ��*/
    if (0 == VOS_StrCmp((TAF_CHAR*)pucCmdName, "+CMGL"))
    {
        if (0 != pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec)
        {
            return AT_SUCCESS;
        }
    }

    switch (pstUsimInfoCtx->enCardStatus)
    {
        case USIMM_CARD_SERVIC_AVAILABLE:
            ulRst = AT_SUCCESS;
            break;
        case USIMM_CARD_SERVIC_SIM_PIN:
            ulRst = AT_CME_SIM_PIN_REQUIRED;
            break;
        case USIMM_CARD_SERVIC_SIM_PUK:
            ulRst = AT_CME_SIM_PUK_REQUIRED;
            break;
        case USIMM_CARD_SERVIC_UNAVAILABLE:
        case USIMM_CARD_SERVIC_NET_LCOK:
        case USIMM_CARD_SERVICE_IMSI_LOCK:
            ulRst = AT_CME_SIM_FAILURE;
            break;
        case USIMM_CARD_SERVIC_ABSENT:
            ulRst = AT_CME_SIM_NOT_INSERTED;
            break;

        case USIMM_CARD_SERVIC_BUTT:

            ulRst = AT_CME_SIM_BUSY;
            break;


        default:
            ulRst = AT_ERROR;
            break;
    }

    return ulRst;
}



/*****************************************************************************
 Prototype      : At_SetMode
 Description    : ����ģʽ
 Input          : ucIndex  --- �û�����ֵ
                  Mode  --- ģʽ
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.��    ��   : 2007-03-27
    ��    ��   : h59254
    �޸�����   : ���ⵥ��:A32D09820(PC-Lint�޸�)

  3.��    ��   : 2007-08-13
    ��    ��   : s62952
    ���ⵥ��   : A32D12683

  4.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ����ONLINE-COMMANDģʽ

  5.��    ��   : 2015��3��31��
    ��    ��   : A00165503
    �޸�����   : DTS2015032704953: HSUART�˿��л���CMD/ONLINE_CMDģʽʱ,
                 ��Ҫ���HSUART�Ļ����������, ��ֹ��ǰ���������ʱ, ������
                 �������ʧ
*****************************************************************************/
VOS_VOID At_SetMode(VOS_UINT8 ucIndex, AT_MODE_TYPE Mode, VOS_UINT8 ucSubMode)
{
    /* ����ONLINE-COMMANDģʽ, ����ģʽ���ֲ���, ����״̬��ΪSTOP */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      && (AT_ONLINE_CMD_MODE == Mode) )
    {
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
    }


    /* �˳�����ģʽ */
    if ( ( (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode)
        || (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode) )
      && (AT_CMD_MODE == Mode) )
    {
        /* Ϊ����Q������һ��,��Ϊ�Ȼ�ӦNO CARRIER��������DCD�źţ�
           ������DCD�źŵĲ���������At_FormatResultData�д���*/

        gastAtClientTab[ucIndex].DataMode = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
        AT_NORM_LOG("At_SetMode exit data mode");
    }

    gastAtClientTab[ucIndex].Mode          = Mode;

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        g_stParseContext[ucIndex].ucMode = ucSubMode;
    }
    else if (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        g_stParseContext[ucIndex].ucMode = ucSubMode;
    }
    else
    {
        gastAtClientTab[ucIndex].DataMode  = ucSubMode;
        gastAtClientTab[ucIndex].DataState = AT_DATA_STOP_STATE;
        AT_NORM_LOG("At_SetMode enter data mode");
    }
}


/*****************************************************************************
 Prototype      : At_CountDigit
 Description    : ������ȡ�����ַ������ض��ַ��ĵڼ��γ��ֵĵ�ַ
                  ע�⣬�ô˺���ʱ���뱣֤������ַ�������ȷ�ԣ�������û�������Ƿ��ַ�
 Input          : pData   --- �����ַ���
                  ulLen   --- �ִ�����
                  Char    --- ���ҵ��ַ�
                  ulIndex --- �ڼ����ַ�
 Output         :
 Return Value   : ���ص�ַָ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
 2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 AT_CountDigit(TAF_UINT8 *pData,TAF_UINT32 ulLen,TAF_UINT8 Char,TAF_UINT32 ulIndex)
{
    TAF_UINT8   *pTmp   = TAF_NULL_PTR;
    TAF_UINT8   *pCheck = TAF_NULL_PTR;
    TAF_UINT32  count   = 0;
    TAF_UINT32  ChkLen  = 0;
    TAF_UINT32  TmpLen  = 0;

    pTmp  = pData;

    /*����������*/
    if( (Char == *pTmp) || (Char == *((pTmp + ulLen) - 1)))
    {
        return 0;
    }

    pCheck = pData;
    while( TmpLen++ < ulLen )
    {
        /*�ж��Ƿ������ֻ������ض��ַ�*/
        if(( (*pCheck >= '0') && (*pCheck <= '9') )|| ((*pCheck == Char) && (*(pCheck+1) != Char)))
        {
            pCheck++;
        }
        else
        {
            return 0;
        }
    }

    while( ChkLen++ < ulLen )
    {
        if(Char == *pTmp)
        {
            count++;
            if(count == ulIndex)
            {
                return ChkLen;
            }
        }
        pTmp++;
    }

    return 0;
}
/*****************************************************************************
 �� �� ��  : At_InterTimerOutProc
 ��������  : AT���ʱ����ʱ����
 �������  : VOS_UINT8  ucIndex �û�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��21��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��24��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50_At_Abort, ��Ӵ������ĳ�ʱ����

  3.��    ��   : 2012��12��28��
    ��    ��   : f62575
    �޸�����   : DTS2012122700666, ���TR1M��ʱ����TC1M��ʱ��ǰ��ʱ����GCF������������CP-ERROR����

  4.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III

  5.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��

  6.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ����UART�˿�PPP����֧��

  7.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : DTS2015032409785: ����ˮ�߼�⹦��
*****************************************************************************/
VOS_VOID At_InterTimerOutProc(
    VOS_UINT8                           ucIndex
)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult;

    pstUartCtx = AT_GetUartCtxAddr();
    ulResult   = AT_FAILURE;

    /*�ڲ�����������Ҫ������������м��*/
    switch(gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_COPS_SET_AUTOMATIC:
        case AT_CMD_COPS_SET_MANUAL:
        case AT_CMD_COPS_SET_DEREGISTER:
        case AT_CMD_COPS_SET_MANUAL_AUTOMATIC_MANUAL:
            ulResult= AT_CME_NETWORK_TIMEOUT;
            break;

        case AT_CMD_CUSD_REQ:
            /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
            /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, end */
            ulResult= AT_CME_NETWORK_TIMEOUT;
            break;

        case AT_CMD_PPP_ORG_SET:
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_REQ);

            /*��PPP����HDLCȥʹ�ܲ���*/
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_HDLC_DISABLE);

            /* ��������ģʽ */
            At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);

            /* ��NO CARRIER��Ϣ */
            ulResult = AT_NO_CARRIER;
            break;

        case AT_CMD_D_IP_CALL_SET:
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_RAW_REQ);

            /*��PPP����HDLCȥʹ�ܲ���*/
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_HDLC_DISABLE);

            ulResult = AT_ERROR;
            break;

        case AT_CMD_H_PS_SET:
        case AT_CMD_PS_DATA_CALL_END_SET:

            /* ��������ģʽ */
            At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);
            ulResult = AT_ERROR;
            break;

        case AT_CMD_SET_TMODE:
            ulResult = AT_ERROR;
            break;

        case AT_CMD_COPS_ABORT_PLMN_LIST:
            ulResult = AT_ABORT;
            break;

        case AT_CMD_ABORT_NETSCAN:
            ulResult = AT_ABORT;
            break;

        case AT_CMD_CMGS_TEXT_SET:
        case AT_CMD_CMGS_PDU_SET:
        case AT_CMD_CMGC_TEXT_SET:
        case AT_CMD_CMGC_PDU_SET:
        case AT_CMD_CMSS_SET:
        case AT_CMD_CMST_SET:
            ulResult = AT_CMS_UNKNOWN_ERROR;
            break;

        case AT_CMD_CPBR2_SET:
            if (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
            {
                pstUartCtx->pWmLowFunc = VOS_NULL_PTR;
            }

            ulResult = AT_ERROR;
            break;

        case AT_CMD_VMSET_SET:
            AT_InitVmSetCtx();
            ulResult = AT_ERROR;
            break;

        default:
            ulResult= AT_ERROR;
            break;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    At_FormatResultData(ucIndex,ulResult);
    return;

}

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/*****************************************************************************
 �� �� ��  : AT_DockHandleCmd
 ��������  : ת��DOCK���͹�����AT���E5ͨ��
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��13��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��11��10��
    ��    ��   : lijun 00171473
    �޸�����   : ����͸����Ӧ�ô����AT����
  3.��    ��   : 2010��12��24��
    ��    ��   : lijun 00171473
    �޸�����   : DTS2010122403722 APDIALMODE���Ӧ����Ӧ�ô���
  4.��    ��   : 2011��10��10��
    ��    ��   : �޾�ǿ/c64416
    �޸�����   : �·����ɱ�־λ�ж��Ƿ�DOCK����
*****************************************************************************/
VOS_UINT32 AT_DockHandleCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          usLength = 0;
    VOS_UINT8                           aucCmdTmp[100] = {0};

    if (usLen > sizeof(aucCmdTmp))
    {
        return AT_FAILURE;
    }

    /* ����AT�����Ӧ��ת����E5 */
    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        if (AT_APP_USER == gastAtClientTab[i].UserType)
        {
            VOS_MemSet(aucCmdTmp, 0x00, sizeof(aucCmdTmp));
            VOS_MemCpy(aucCmdTmp, pucData, usLen);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s%s%s",
                                gaucAtCrLf, aucCmdTmp, gaucAtCrLf);
            At_SendResultData(i, pgucAtSndCodeAddr, usLength);
            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_MatchCmdName
 Description    : ������ƥ��
 Input          : ucIndex  --- �û�����ֵ
                  CmdType  --- ��������
                  pRetName --- ���������ص�ַ
                  pRetPara --- �����ű����ص�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_MatchCmdName (TAF_UINT16 ucIndex,TAF_UINT32 CmdType)
{
    /*  */
    return AT_FAILURE;
}


/*****************************************************************************
 �� �� ��  : AT_HandleDockSetCmd
 ��������  : ����DOCK��������,��ʽ�������ַ���
 �������  : ucIndex - �û�����
             pucData - ������ַ���
             usLen   - ����
 �������  : ��
 �� �� ֵ  : AT_SUCCESS - ��DOCK��������
             AT_FAILURE - ����DOCK��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��26��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort, ����������Ϣ, ��ϴ�����ʹ��
*****************************************************************************/
VOS_UINT32 AT_HandleDockSetCmd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_ParseSetDockCmd(pucData, usLen);
    if (AT_SUCCESS != ulResult)
    {
        return AT_FAILURE;
    }

    if (AT_FAILURE == At_MatchCmdName(ucIndex, gucAtCmdFmtType))
    {
        At_FormatResultData(ucIndex, AT_CMD_NOT_SUPPORT);
        return AT_SUCCESS;
    }


    AT_SaveCmdElementInfo(ucIndex, (VOS_UINT8*)"^DOCK", AT_EXTEND_CMD_TYPE);

    ulResult = At_SetParaCmd(ucIndex);

    At_FormatResultData(ucIndex, ulResult);

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_RcvTiS0Expired
 ��������  : ����S0��ʱ����ʱ
 �������  : REL_TIMER_MSG                      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��5��28��
    ��    ��   : L60609
    �޸�����   : DTS2013052807080

  3.��    ��   : 2014��2��14��
    ��    ��   : j00174725
    �޸�����   : TQE

  4.��    ��   : 2015��5��29��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID AT_RcvTiS0Expired(
    REL_TIMER_MSG                      *pstMsg
)
{
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtParam;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT16                          usReqClientId;

    /* ����timer name��ȡ�����ĸ�index */
    ucClientIndex = (VOS_UINT8)(pstMsg->ulName >> 12);

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucClientIndex);

    PS_MEM_SET(&stCallMgmtParam, 0, sizeof(MN_CALL_SUPS_PARAM_STRU));

    /* Ŀǰֻ��voice֧���Զ��������ܣ�calltype �̶���Ϊvoice */
    stCallMgmtParam.enCallType    = MN_CALL_TYPE_VOICE;
    stCallMgmtParam.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;

    stCallMgmtParam.callId = (MN_CALL_ID_T)pstMsg->ulPara;

    /* ����ClientIdΪ�㲥ClientId 0x3fff����0x7fff��
       AT�ڴ���incoming�¼�ʱ���ж��������Զ�������������ʱ��ʱulName�д�����Client Index��0x3f����0x7f
       ���Դ˴�����MN_CALL_Supsʱ��Ҫ��ClientId
    */
    if (AT_BROADCAST_CLIENT_INDEX_MODEM_0 == ucClientIndex)
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    }
    else if (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == ucClientIndex)
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;
    }
    else
    {
        usReqClientId = AT_BROADCAST_CLIENT_ID_MODEM_2;
    }

    if (AT_SUCCESS != MN_CALL_Sups(usReqClientId, 0, &stCallMgmtParam))
    {
        AT_WARN_LOG("AT_ProcTimerS0: S0 Answer Fail");
    }
    pstCcCtx->stS0TimeInfo.bTimerStart = TAF_FALSE;
    pstCcCtx->stS0TimeInfo.ulTimerName = 0;

    return;
}

/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

/*****************************************************************************
 Prototype      : At_TimeOutProc
 Description    : ATCģ�鳬ʱ����
 Input          : pMsg   --- ��ʱ��Ϣ��
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    ��   : 2010��5��14��
    ��    ��   : z00161729
    �޸�����   : �������ⵥ��A32D19317:�Զ�����û��^CONN�ϱ�
  3.��    ��   : 2010��9��26��
    ��    ��   : w00166186
    �޸�����   : ֧�ֺ�̨^DTMF
  4.��    ��   : 2010��11��09��
    ��    ��   : s62952
    �޸�����   : ���ⵥ��:DTS2010110502657���貦���ϱ�̬Ƶ��������AT����
  5.��    ��   : 2011��06��09��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2011060304914,��E353s-2װ��AT 2011.6.2���·�AT^TMODE=2/3�󣬵��岻�᷵��OK
                 ����ֱ���л�ģʽ���Ա�E367u����OK���ٽ����л�
  6.��    ��   : 2013��2��21��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III

  7.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: RING�Ŷ�ʱ����ʱ����
*****************************************************************************/
TAF_VOID At_TimeOutProc(
    REL_TIMER_MSG                       *pMsg
)
{
    /* �ֲ�������������ʼ�� */
    VOS_UINT8                           ucIndex;

    if (VOS_NULL_PTR == pMsg)
    {
        AT_WARN_LOG("At_TimeOutProc pMsg is NULL");
        return;
    }

    ucIndex = (VOS_UINT8)pMsg->ulName;
    if (AT_INTERNAL_PROCESS_TYPE == (pMsg->ulName & 0x00000f00))
    {
        switch(pMsg->ulName & 0x000000ff)
        {
            /* �Զ�Ӧ�����AT������������ϱ�������״̬�£��൱�ڽ����ˣ�����û��ָʾ */
            case AT_S0_TIMER:
                AT_RcvTiS0Expired(pMsg);
                break;

            case AT_HOLD_CMD_TIMER:
                ucIndex = (VOS_UINT8)((pMsg->ulName)>>12);
                AT_BlockCmdTimeOutProc(ucIndex);
                break;


            /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */

            case AT_SHUTDOWN_TIMER:
                mdrv_sysboot_shutdown();
                break;
    /* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */


            default:
                break;
        }
        return;
    }
    else
    {
        ucIndex = (VOS_UINT8)pMsg->ulName;
        if(ucIndex >= AT_MAX_CLIENT_NUM)
        {
            AT_WARN_LOG("At_TimeOutProc FAILURE");
            return;
        }

        if(AT_CMD_CURRENT_OPT_BUTT == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_WARN_LOG("At_TimeOutProc AT_CMD_CURRENT_OPT_BUTT");
            return;
        }

        AT_LOG1("At_TimeOutProc ucIndex:",ucIndex);
        AT_LOG1("At_TimeOutProc gastAtClientTab[ucIndex].CmdCurrentOpt:",gastAtClientTab[ucIndex].CmdCurrentOpt);

        At_InterTimerOutProc(ucIndex);

    }
}
/*****************************************************************************
 Prototype      : At_GetStrContent
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT8* At_GetStrContent(TAF_UINT32 ulType)
{
    if(ulType < AT_STRING_BUTT)
    {
        return gastAtStringTab[ulType].pucText;
    }
    else
    {
        return gastAtStringTab[AT_STRING_BUTT].pucText;
    }
}

/* PC������AT��A���Ƶ�C��, At_sprintf���ظ�����,���ڴ˴������������� */
/*lint -e960 �޸���:l60609;ԭ��:64bit*/
/*lint +e960 �޸���:l60609;ԭ��:64bit*/

/*****************************************************************************
 Prototype      : At_sprintf
 Description    :
 Input          :
 Output         :
 Return Value   : ���ص�ַָ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��29��
    ��    ��   : c64416
    �޸�����   : AT�ں���Ŀ����ֲV7R1�ĵ��ýӿ�
*****************************************************************************/
/*lint -esym(960,69) �޸��ˣ����� 44270������:s62952;ԭ��������ɱ��������Ҫ���� */
/*lint -esym(961,47) �޸��ˣ����� 44270������:s62952;ԭ��������ɱ��������Ҫ���� */
/*lint -e713 -e438 -e507*/
VOS_INT32 At_sprintf(VOS_INT32 MaxLength,VOS_CHAR *pHeadAddr,VOS_CHAR *pCurrAddr,const VOS_CHAR *fmt,...)
{
    VOS_INT32 slLength = 0;
    VOS_UINT32 ulNum = 0;
    VOS_INT32 lNumSrc = 0;      /* ԭʼ���� */
    VOS_INT32 slNum = 0;        /* ת��������� */
    VOS_UINT32 ulSignFlag = VOS_FALSE;
    VOS_CHAR *pData = NULL;
    VOS_CHAR *sc = NULL;
    VOS_CHAR *s = NULL;
    va_list args;
    VOS_UINT32 ulLen1 = 0, ulLen2 = 0;   /* ulLen1:%�����õĳ���; ulLen2:ʵ�ʶ�ȡ�ĳ��� */

    if(pCurrAddr < pHeadAddr)
    {
        return 0;
    }

    va_start(args, fmt);
    for (pData = (VOS_CHAR *)fmt; '\0' != *pData ; ++pData)
    {
        if('%' == *pData)
        {
            ulLen1 = 0;
            ulLen2 = 0;

            pData++;

            if('+' == (*pData) && 'd' == *(pData + 1))
            {
                pData++;
                ulSignFlag = VOS_TRUE;
                ulLen1 = 0;     /* �з������ʹ�ӡ���� */
            }

            if('0' == (*pData))
            {
                pData++;
                ulLen1 = 0;     /* ָ���Ŀ�ȣ������ */
            }

            /* Ŀǰ��ֻ֧��С�ڵ���9λ�Ŀ�� */
            if(('0' <= (*pData)) && ('9' >= (*pData)))
            {
                ulLen1 = (VOS_UINT32)(VOS_INT32)((*pData) - '0');     /* ָ���Ŀ�� */
                pData++;
            }

            /* Ŀǰ��ֻ���õ�d,s,X,���֣�����һ����Ϊ���� */
            switch(*pData)
            {
            case 'c':
                {
                    slLength++;
                    break;
                }

            case 's':
                s = va_arg(args, VOS_CHAR *);
                if(NULL == s)
                {
                    slLength += (VOS_INT32)strlen("(null)");
                    break;
                }

                for (sc = s; *sc != '\0'; ++sc)
                {
                    slLength++;
                }
                break;

            case 'd':
                lNumSrc = va_arg(args, VOS_INT32);
                slNum = lNumSrc;

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ�� */

                while ((slNum > 9) || (slNum < (-9)))
                {
                    slNum = slNum / 10;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ�� */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                else if(lNumSrc < 0 || ulSignFlag == VOS_TRUE)    /* ���ulLen2 >= ulLen1,��lNumSrc<0����Ҫ���ϸ��ŵ�һ���ռ� */
                {
                    slLength++;
                    ulSignFlag = VOS_FALSE;
                }
                else
                {
                }
                break;

            case 'u':
                ulNum = va_arg(args, VOS_UINT32);

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ�� */
                while (ulNum > 9)
                {
                    ulNum = ulNum / 10;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ�� */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            case 'X':
                /* continue */
            case 'x':
                ulNum = va_arg(args, VOS_UINT32);

                slLength++;
                ulLen2++;                   /* ʵ�ʵĿ�� */

                while (ulNum > 0x0f)
                {
                    ulNum = ulNum / 16;
                    slLength++;
                    ulLen2++;               /* ʵ�ʵĿ�� */
                }

                if(ulLen2 < ulLen1)
                {
                    slLength += (VOS_INT32)(ulLen1- ulLen2);
                }
                break;

            default:
                va_end(args);
                return 0;
            }
        }
        else
        {
            slLength++;     /* ��1 */
        }
    }
    va_end(args);

    if(pCurrAddr - pHeadAddr + slLength >= (VOS_INT32)(MaxLength))
    {
        return 0;
    }

    va_start(args, fmt);

    if(slLength != VOS_vsprintf(pCurrAddr,fmt,args))
    {
        va_end(args);
        return 0;
    }

    va_end(args);

    return slLength;
}

/*lint +e713 +e438 +e507*/
/*lint +esym(960,69) �޸��ˣ����� 44270�������ˣ�s62952*/
/*lint +esym(961,47)  �޸��ˣ����� 44270�������ˣ�s62952*/

/*lint -esym(960,69) �޸��ˣ����� 44270������:s62952;ԭ��������ɱ��������Ҫ���� */
/*lint -esym(961,47) �޸��ˣ����� 44270������:s62952;ԭ��������ɱ��������Ҫ���� */
/*lint -e713 -e438 -e507*/
/*****************************************************************************
 Prototype      : At_sprintfUnsigned
 Description    : �޷��������������
 Input          :
 Output         :
 Return Value   : ���ص�ַָ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-09-15
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_INT32 At_sprintfUnsigned(TAF_INT32 MaxLength,TAF_CHAR *headaddr,TAF_CHAR *curraddr,const TAF_CHAR *fmt,...)
{
    TAF_INT32  Length = 0;
    TAF_UINT32 ulnum = 0;
    TAF_CHAR *pData = TAF_NULL_PTR;
    TAF_CHAR *sc = TAF_NULL_PTR;
    TAF_CHAR *s = TAF_NULL_PTR;
    va_list args;

    if(curraddr < headaddr)
    {
        AT_ERR_LOG("At_sprintf curraddr < headaddr");
        return 0;
    }

    va_start(args, fmt);
    for (pData = (TAF_CHAR*)fmt; '\0' != *pData ; ++pData)
    {
        if('%' == *pData)
        {
            pData++;
            /* Ŀǰ��ֻ���õ�d,s,X,���֣�����һ����Ϊ���� */
            switch(*pData)
            {
            case 's':
                s = (TAF_CHAR *)va_arg(args, TAF_INT8 *);

                for (sc = s; *sc != '\0'; ++sc)
                {
                    Length++;
                }
                break;

            case 'd':
                ulnum = va_arg(args, TAF_UINT32);

                Length++;

                while (ulnum > 9)
                {
                    ulnum = ulnum / 10;
                    Length++;
                }
                break;

            case 'X':
                ulnum = va_arg(args, TAF_UINT32);

                Length++;
                while (ulnum > 0x0f)
                {
                    ulnum = ulnum / 16;
                    Length++;
                }
                break;

            case '0':
                ulnum = va_arg(args, TAF_UINT32);
                pData++;                                                        /*ָ����峤��*/

                Length += (*pData - '0');
                pData++;                                                        /*����X�ַ�*/
                break;

            default:
                AT_ERR_LOG("At_sprintf ERROR case");
                va_end(args);
                return 0;
            }
        }
        else
        {
            Length++;     /* ��1 */
        }
    }
    va_end(args);

    if(((curraddr - headaddr) + Length) >= MaxLength)
    {
        AT_ERR_LOG("At_sprintf too long");
        return 0;
    }

    va_start(args, fmt);
    if(Length != VOS_vsprintf(curraddr,fmt,args))
    {
        AT_ERR_LOG("At_sprintf Length is ERROR!");
    }
    va_end(args);

    return Length;
}
/*lint +e713 +e438 +e507*/
/*lint +esym(960,69) �޸��ˣ����� 44270�������ˣ�s62952*/
/*lint +esym(961,47)  �޸��ˣ����� 44270�������ˣ�s62952*/

/*****************************************************************************
 Prototype      : AT_MapCallTypeModeToClccMode
 Description    :
 Input          :
 Output         :
 Return Value   : ���ص�ַָ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-14
    Author      : ---
    Modification: Created function
 2.��    ��   : 2011��10��22��
   ��    ��   : f00179208
   �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
TAF_VOID AT_MapCallTypeModeToClccMode(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_UINT8                          *penClccMode
)
{
    switch(enCallType)
    {
    case MN_CALL_TYPE_VOICE:
    case MN_CALL_TYPE_EMERGENCY:
    /* Added by n00269697 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
    case MN_CALL_TYPE_MIEC :
    case MN_CALL_TYPE_AIEC :
    case MN_CALL_TYPE_TEST :
    case MN_CALL_TYPE_RECFGURATION :
    case MN_CALL_TYPE_PSAP_ECALL:
    /* Added by n00269697 for V3R3C60_eCall��Ŀ, 2014-3-29, end */
        *penClccMode = 0;
        break;
    case MN_CALL_TYPE_FAX:
        *penClccMode = 2;
        break;
    default:
        *penClccMode = 1;
        break;
    }
}


/*****************************************************************************
 Prototype      : At_GetMnOptType
 Description    :
 Input          :
 Output         :
 Return Value   : ����AT��������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-14
    Author      : ---
    Modification: Created function

  2.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : �޸�Ȧ���Ӷ�
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ  :ɾ��NAS_FEATURE_CCBS��
  4.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control: SS��������
*****************************************************************************/
AT_CMD_CURRENT_OPT_ENUM At_GetMnOptType(MN_MMI_OPERATION_TYPE_ENUM_U8 enType)
{
    switch(enType)
    {
    case TAF_MMI_CALL_ORIG:/* TAF_MMI_CALL_ORIG */
        return AT_CMD_D_CS_VOICE_CALL_SET;
    case TAF_MMI_CALL_CHLD_REQ:/* TAF_MMI_CALL_CHLD_REQ */
        return AT_CMD_CHLD_SET;
    case TAF_MMI_CHANGE_PIN:/* TAF_MMI_CHANGE_PIN */
        return AT_CMD_CPIN_UNBLOCK_SET;
    case TAF_MMI_CHANGE_PIN2:/* TAF_MMI_CHANGE_PIN2 */
        return AT_CMD_CPIN2_UNBLOCK_SET;
    case TAF_MMI_UNBLOCK_PIN:/* TAF_MMI_UNBLOCK_PIN */
        return AT_CMD_CPIN_VERIFY_SET;
    case TAF_MMI_UNBLOCK_PIN2:/* TAF_MMI_UNBLOCK_PIN2 */
        return AT_CMD_CPIN2_VERIFY_SET;
    case TAF_MMI_REGISTER_SS:/* TAF_MMI_REGISTER_SS */
        return AT_CMD_SS_REGISTER;
    case TAF_MMI_ERASE_SS:/* TAF_MMI_ERASE_SS */
        return AT_CMD_SS_ERASE;
    case TAF_MMI_ACTIVATE_SS:/* TAF_MMI_ACTIVATE_SS */
        return AT_CMD_SS_ACTIVATE;
    case TAF_MMI_DEACTIVATE_SS:/* TAF_MMI_DEACTIVATE_SS */
        return AT_CMD_SS_DEACTIVATE;
    case TAF_MMI_INTERROGATE_SS:/* TAF_MMI_INTERROGATE_SS */
        return AT_CMD_SS_INTERROGATE;
    case TAF_MMI_REGISTER_PASSWD:/* TAF_MMI_REGISTER_PASSWD */
        return AT_CMD_SS_REGISTER_PSWD;
	/* Delete TAF_MMI_GET_PASSWD��֧ */
    case TAF_MMI_PROCESS_USSD_REQ:/* TAF_MMI_PROCESS_USSD_REQ */
        return AT_CMD_SS_USSD;
    case TAF_MMI_SUPPRESS_CLIP:/* TAF_MMI_SUPPRESS_CLIP */
        return AT_CMD_CLIP_READ;
    case TAF_MMI_INVOKE_CLIP:/* TAF_MMI_INVOKE_CLIP */
        return AT_CMD_CLIP_READ;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    case TAF_MMI_DEACTIVATE_CCBS:/* TAF_MMI_DEACTIVATE_CCBS */
        return AT_CMD_SS_DEACTIVE_CCBS;

    case TAF_MMI_INTERROGATE_CCBS:
        return AT_CMD_SS_INTERROGATE_CCBS;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    default:
        break;

    }

    return AT_CMD_INVALID;
}

/*****************************************************************************
 �� �� ��  : At_UnlockSimLock
 ��������  : ֧��AT^SIMLOCK��������
 �������  : VOS_UINT8  ucIndex �û�����
             pucData -- �Զ��ſ�ʼ�Ĳ�������
             usLen--��ǰ�Ӷ��ſ�ʼ�Ĳ����ĳ���
 �������  : ��
 �� �� ֵ  : AT_OK --- �ɹ�
             AT_ERROR --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��10��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��11��3��
    ��    ��   : C00173809
    �޸�����   : AT�ں���Ŀ��SIMLOCK���ú�����Ϊ�첽��Ϣ��
  3.��    ��   : 2012��01��29��
    ��    ��   : l00171473
    �޸�����   : DTSDTS2012013000257,SIMLOCK�㷨�汾����Ϊ2.0��ء�
  4.��    ��   : 2012��2��20��
    ��    ��   : l60609
    �޸�����   : B060 Prj:ATɾ��ȫ�ֱ���g_ucAtSimLockErrTimes
*****************************************************************************/
VOS_UINT32 At_UnlockSimLock(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
)
{
    AT_PARSE_PARA_TYPE_STRU            *pstPwdPara;
    DRV_AGENT_SIMLOCK_SET_REQ_STRU      stSimlockReq;

    stSimlockReq.ulPwdLen    = 0;

    if (ulParaCnt == 2)
    {
        pstPwdPara              = (AT_PARSE_PARA_TYPE_STRU*)(pstParalist + 1);

        if (TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX  == pstPwdPara->usParaLen)
        {
            if (AT_FAILURE != At_CheckNumString(pstPwdPara->aucPara,
                                                TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX))
            {
                stSimlockReq.ulPwdLen    = TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX;

                PS_MEM_CPY(stSimlockReq.aucPwd, pstPwdPara->aucPara, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
                /* Modified by l00171473 for DTS2012013000257 SIMLOCK�㷨�汾����Ϊ2.0���, 2012-01-29, Begin */
                stSimlockReq.aucPwd[stSimlockReq.ulPwdLen] = 0;
                /* Modified by l00171473 for DTS2012013000257 SIMLOCK�㷨�汾����Ϊ2.0���, 2012-01-29, End */
            }
        }
    }

    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                  gastAtClientTab[ucIndex].opId,
                                                  DRV_AGENT_SIMLOCK_SET_REQ,
                                                  &stSimlockReq,
                                                  sizeof(stSimlockReq),
                                                  I0_WUEPS_PID_DRV_AGENT))
    {
        /*���õ�ǰ����ģʽ */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ;

        /* ����SIMLOCK���⴦�����Ｔʹ���صȴ��첽��Ϣ������Ҳ������ʱ��*/
        if(AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
        {
            At_FormatResultData(ucIndex, AT_ERROR);
            return VOS_ERR;
        }

        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

        return VOS_OK;
    }

    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_ERR;

}

/* Added by L60609 for AT Project��2011-10-10,  Begin*/
/*****************************************************************************
 �� �� ��  : AT_RcvFuncReg
 ��������  : ��¼������˿ڶ�Ӧ�Ľ������ݺ���
 �������  : AT_PHY_PORT_ENUM_UINT32 ulPhyPort
             pAtDataRcvFunc pRcvFunc
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_RcvFuncReg(AT_PHY_PORT_ENUM_UINT32 ulPhyPort, CPM_RCV_FUNC pRcvFunc)
{
    /*check para*/
    if (AT_PORT_BUTT <= ulPhyPort)
    {
        AT_ERR_LOG("AT_RcvFuncReg: PHY PORT ERR!");
        return;
    }

    if (VOS_NULL_PTR == pRcvFunc)
    {
        AT_ERR_LOG("AT_RcvFuncReg: pRcvFunc is NULL!");
        return;
    }

    g_apAtPortDataRcvFuncTab[ulPhyPort] = pRcvFunc;
}


/* Added by L60609 for AT Project��2011-10-10,  End*/

/*****************************************************************************
 �� �� ��  : At_ProcXmlText
 ��������  : XML�ı����봦����
 �������  : VOS_UINT8  ucIndex ͨ������
             TAF_UINT8 *pData   ��������
             TAF_UINT16 usLen   ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_ProcXmlText ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    VOS_UINT16                              usTmpLen;
    AT_XML_PROC_TYPE_ENUM_UINT8             enXmlProcType;
    AT_MTA_CPOS_REQ_STRU                   *pstCposSetReq;
    VOS_UINT32                              ulResult;
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    AT_MODEM_AGPS_CTX_STRU                 *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* �ֲ�������ʼ�� */
    usTmpLen           = usLen;
    enXmlProcType      = AT_XML_PROC_TYPE_BUTT;
    enCposOpType       = MTA_AT_CPOS_BUTT;

    /* �յ�"Ctrl-Z"�ַ������ͱ�����Ϣ */
    if (AT_CTRL_Z == pData[usTmpLen - 1])
    {
        usTmpLen       -= 1;
        enXmlProcType  = AT_XML_PROC_TYPE_FINISH;
        enCposOpType   = MTA_AT_CPOS_SEND;
    }
    /* �յ�"CR"�ַ��������ȴ����� */
    else if (AT_CR == pData[usTmpLen - 1])
    {
        enXmlProcType  = AT_XML_PROC_TYPE_CONTINUE;
    }
    /* �յ�"ESC"�ַ���ȡ��������Ϣ���� */
    else if (AT_ESC == pData[usTmpLen - 1])
    {
        usTmpLen       -= 1;
        enXmlProcType  = AT_XML_PROC_TYPE_FINISH;
        enCposOpType   = MTA_AT_CPOS_CANCEL;
    }
    else
    {
        return AT_ERROR;
    }

    /* �ѻ��������ַ��ӵ�XML������ */
    if (MTA_AT_CPOS_CANCEL != enCposOpType)
    {
        /* XML���������ж� */
        if (AT_XML_MAX_LEN < ((pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead) + usTmpLen))
        {
            return AT_ERROR;
        }

        PS_MEM_CPY(pstAgpsCtx->stXml.pcXmlTextCur,
                   pData,
                   usTmpLen);

        pstAgpsCtx->stXml.pcXmlTextCur += usTmpLen;
    }

    /* �·�XML����������ȴ����� */
    if (AT_XML_PROC_TYPE_FINISH == enXmlProcType)
    {
        pstCposSetReq = (AT_MTA_CPOS_REQ_STRU*)PS_MEM_ALLOC( WUEPS_PID_AT,
                                                             sizeof(AT_MTA_CPOS_REQ_STRU));
        if (VOS_NULL_PTR == pstCposSetReq)
        {
            AT_ERR_LOG("At_ProcXmlText: Memory malloc failed!");
            return AT_ERROR;
        }
        PS_MEM_SET(pstCposSetReq, 0x00, sizeof(AT_MTA_CPOS_REQ_STRU));

        /* ��д��Ϣ�ṹ */
        pstCposSetReq->enCposOpType = enCposOpType;

        /* ���û�������Ctrl-Z�Ž���������MTA */
        if (MTA_AT_CPOS_SEND == enCposOpType)
        {
            pstCposSetReq->ulXmlLength  = (VOS_UINT32)(pstAgpsCtx->stXml.pcXmlTextCur - pstAgpsCtx->stXml.pcXmlTextHead);
            PS_MEM_CPY(pstCposSetReq->acXmlText,
                       pstAgpsCtx->stXml.pcXmlTextHead,
                       pstCposSetReq->ulXmlLength);
        }

        /* ���͵�MTAģ�� */
        ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                          gastAtClientTab[ucIndex].opId,
                                          ID_AT_MTA_CPOS_SET_REQ,
                                          pstCposSetReq,
                                          sizeof(AT_MTA_CPOS_REQ_STRU),
                                          I0_UEPS_PID_MTA);

        /* �ͷ�XML�����ṹ */
        PS_MEM_FREE(WUEPS_PID_AT, pstCposSetReq);

        if (TAF_SUCCESS != ulResult)
        {
            AT_ERR_LOG("At_ProcXmlText: AT_FillAndSndAppReqMsg fail.");
            return AT_ERROR;
        }

        /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOS_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_WAIT_XML_INPUT;
}

/* ɾ��^EOPLMN��������Ĳ�������������ʹ��ͨ��AT�������������� */

/*****************************************************************************
 �� �� ��  : At_CheckCurrRatModeIsCL
 ��������  : �жϵ�ǰ�Ľ���ģʽ��CL
 �������  : TAF_UINT8  ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32 �����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 At_CheckCurrRatModeIsCL (
    VOS_UINT8                           ucIndex
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    VOS_UINT8                          *pucIsCLMode = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    /* ��ȡmodemidʧ�ܣ�Ĭ�ϲ�������Ӧ��AT���� */
    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_CurrRatModeIsCL:Get Modem Id fail!");
        return VOS_FALSE;
    }

    pucIsCLMode = AT_GetModemCLModeCtxAddrFromModemId(enModemId);

    if (VOS_TRUE == *pucIsCLMode)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

