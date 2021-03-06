/**********************************************************************/
/*                                                                    */
/*                 Licensed Materials - Property of IBM               */
/*          � Copyright IBM Corp. 2000   All Rights Reserved          */
/*                                                                    */
/**********************************************************************/

#include "dis.h"

/* Opcode Forms:	
			Primary		Extended	Example (page #)
			-------		--------	----------------
	B1		0-3		31-31		47
	B2		0-3		30-31		80
	B8		0-3		24-31		48
	D3		0-3		29-31		68
	D4		0-3		28-31		67
	D5		0-3		27-31		60
	D10		0-3		22-31		89
	I0		0-3		None		110
	I1		0-3		31-31		100
	I3		0-3		29-31		104
	I4		0-3		29-31		115
	I5		0-3		27-31		93
	I6		0-3		26-31		91
	I8		0-3		24-31		86
	I10		0-3		22-31		88
	M0		0-3		None		121
	M1		0-3		31-31		119
	X4		0-3		28-31		108
	X6		0-3		26-31		113
	X10		0-3		22-31		84
*/

OPCODE for_ops[] = {
{0,	1,	'X',	10,	"nop",		116},
{0,	127,	'X',	10,	"nop7f",	0},
{0,	128,	'X',	10,	"mcrf",		84},
{0,	129,	'X',	10,	"mcrfi",	84},
{0,	130,	'X',	10,	"mcrfs",	134},
{0,	131,	'X',	10,	"mcrxr",	133},
{0,	132,	'X',	10,	"mcrxrt",	133},
{0,	133,	'X',	10,	"mfcr",		85},
{0,	134,	'X',	10,	"mfcrf",	84},
{0,	135,	'X',	10,	"mffs",		134},
{0,	136,	'X',	10,	"mfspr",	132},
{0,	137,	'X',	10,	"msracb",	116},
{0,	138,	'X',	10,	"mtcr",		85},
{0,	139,	'X',	10,	"mtcrf",	84},
{0,	140,	'X',	10,	"mtfsb0",	135},
{0,	141,	'X',	10,	"mtfsb1",	135},
{0,	142,	'X',	10,	"mtfsf",	135},
{0,	143,	'X',	10,	"mtfsfi",	134},
{0,	144,	'X',	10,	"mtspr",	131},
{0,	256,	'X',	10,	"mulhd",	156},
{0,	257,	'X',	10,	"mulhdu",	156},
{0,	258,	'X',	10,	"mulhw",	157},
{0,	259,	'X',	10,	"mulhwu",	157},
{0,	260,	'X',	10,	"mulld",	155},
{0,	261,	'X',	10,	"mullw",	156},
{0,	262,	'X',	10,	"divd",		157},
{0,	263,	'X',	10,	"divdu",	158},
{0,	264,	'X',	10,	"divw",		158},
{0,	265,	'X',	10,	"divwu",	159},
{0,	266,	'X',	10,	"fabs",		160},
{0,	267,	'X',	10,	"fadd",		161},
{0,	268,	'X',	10,	"fadds",	161},
{0,	269,	'X',	10,	"fcdtsd",	171},
{0,	270,	'X',	10,	"fcfid",	170},
{0,	271,	'X',	10,	"fcmpo",	173},
{0,	272,	'X',	10,	"fcmpu",	172},
{0,	273,	'X',	10,	"fcsdtd",	171},
{0,	274,	'X',	10,	"fctid",	168},
{0,	275,	'X',	10,	"fctidz",	168},
{0,	276,	'X',	10,	"fctiw",	169},
{0,	277,	'X',	10,	"fctiwz",	169},
{0,	278,	'X',	10,	"fdiv",		162},
{0,	279,	'X',	10,	"fdivs",	162},

{0,	280,	'X',	10,	"fmr",		160},
{0,	281,	'X',	10,	"fmul",		162},
{0,	282,	'X',	10,	"fmuls",	162},
{0,	283,	'X',	10,	"fnabs",	160},
{0,	284,	'X',	10,	"fneg",		160},
{0,	285,	'X',	10,	"fres",		163},
{0,	286,	'X',	10,	"frsp",		167},
{0,	287,	'X',	10,	"frsqrte",	164},
{0,	288,	'X',	10,	"fsqrt",	163},
{0,	289,	'X',	10,	"fsqrts",	163},
{0,	290,	'X',	10,	"fsub",		161},
{0,	291,	'X',	10,	"fsubs",	161},
{0,	512,	'X',	10,	"cmp",		99},
{0,	513,	'X',	10,	"cmpl",		100},
{0,	514,	'X',	10,	"cmpla",	101},
{0,	515,	'X',	10,	"cntlzd",	115},
{0,	516,	'X',	10,	"cntlzw",	115},
{0,	517,	'X',	10,	"crand",	81},
{0,	518,	'X',	10,	"crandc",	83},
{0,	519,	'X',	10,	"creqv",	82},
{0,	520,	'X',	10,	"crnand",	82},
{0,	521,	'X',	10,	"crnor",	82},
{0,	522,	'X',	10,	"cror",		81},
{0,	523,	'X',	10,	"crorc",	83},
{0,	524,	'X',	10,	"crxor",	82},
{0,	525,	'X',	10,	"csct",		80},
{0,	530,	'X',	10,	"cslr",		90},
{0,	531,	'X',	10,	"dsixes",	129},
{0,	532,	'X',	10,	"dtcs",		130},
{0,	533,	'X',	10,	"extsb",	114},
{0,	534,	'X',	10,	"extsw",	114},
{0,	535,	'X',	10,	"extsh",	114},
{0,	536,	'X',	10,	"lssd",		73},
{0,	537,	'X',	10,	"lssw",		72},
{0,	538,	'X',	10,	"rssd",		74},
{0,	539,	'X',	10,	"rssw",		73},
{0,	540,	'X',	10,	"neg",		97},
{0,	541,	'X',	10,	"settag",	132},
{0,	543,	'X',	10,	"td",		105},
{0,	544,	'X',	10,	"tdl",		105},
{0,	545,	'X',	10,	"tw",		106},
{0,	546,	'X',	10,	"twl",		106},

{0,	547,	'X',	10,	"txer",		107},
{0,	548,	'X',	10,	"xerx",		87},
{0,	549,	'X',	10,	"maskg",	115},
{0,	550,	'X',	10,	"xov",		87},
{0,	551,	'X',	10,	"scv",		49},
{0,	552,	'X',	10,	"bri",		48},
{0,	553,	'X',	10,	"sc",		49},
{0,	554,	'X',	10,	"sync",		79},
{0,	555,	'X',	10,	"addze",	96},
{0,	556,	'X',	10,	"subfze",	97},
{0,	557,	'X',	10,	"addme",	95},
{0,	558,	'X',	10,	"subfme",	96},
{0,	559,	'X',	10,	"adda",		97},
{0,	560,	'X',	10,	"xadd",		88},
{0,	561,	'I',	10,	"xaddi",	88},
{0,	562,	'D',	10,	"xstd",		89},
{0,	563,	'D',	10,	"xstw",		89},
{1,	0,	'I',	0,	"andi",		110},
{2,	0,	'I',	0,	"xori",		111},
{3,	0,	'I',	0,	"ori",		111},
{4,	0,	'I',	0,	"addi",		92},
{5,	0,	'I',	0,	"subfic",	94},
{6,	0,	'I',	0,	"mulli",	155},
{7,	0,	'M',	0,	"rlwnm",	121},
{8,	0,	'M',	1,	"rlwinm",	119},
{8,	1,	'B',	1,	"skip",		47},
{9,	0,	'I',	1,	"cmpli",	100},
{9,	1,	'I',	1,	"cmpi",		99},
{10,	0,	'B',	2,	"cbri",		80},
{10,	3,	'D',	3,	"stspr",	68},
{10,	7,	'D',	3,	"ldspr",	68},
{11,	0,	'I',	3,	"twil",		104},
{11,	1,	'I',	3,	"tdi",		103},
{11,	2,	'I',	3,	"twi",		104},
{11,	3,	'I',	3,	"tdil",		103},
{11,	5,	'D',	4,	"ltocwz",	67},
{11,	6,	'X',	4,	"selii",	108},
{11,	7,	'X',	4,	"selri",	109},
{11,	13,	'D',	4,	"ltocd",	67},
{11,	14,	'X',	4,	"selir",	108},
{11,	15,	'X',	4,	"selrr",	109},
{12,	0,	'D',	4,	"lhbr",		65},

{12,	1,	'D',	4,	"lhz",		56},
{12,	2,	'D',	4,	"lwz",		57},
{12,	3,	'D',	4,	"ldar",		76},
{12,	4,	'D',	4,	"lql",		58},
{12,	5,	'D',	4,	"lswz",		70},
{12,	6,	'D',	4,	"lfd",		62},
{12,	7,	'D',	4,	"lwbr",		65},
{12,	8,	'D',	4,	"lbz",		56},
{12,	9,	'D',	4,	"ld",		57},
{12,	10,	'D',	4,	"lsd",		70},
{12,	11,	'D',	4,	"lwa",		57},
{12,	12,	'D',	4,	"lqh",		58},
{12,	13,	'D',	4,	"lwar",		76},
{12,	14,	'D',	4,	"lfs",		62},
{12,	15,	'D',	4,	"lha",		56},
{13,	0,	'X',	4,	"fmadd",	165},
{13,	1,	'X',	4,	"fmadds",	165},
{13,	2,	'X',	4,	"fmsub",	165},
{13,	3,	'X',	4,	"fmsubs",	165},
{13,	4,	'X',	4,	"fnmadd",	166},
{13,	5,	'X',	4,	"fnmadds",	166},
{13,	6,	'X',	4,	"fnmsub",	166},
{13,	7,	'X',	4,	"fnmsubs",	166},
{13,	8,	'X',	4,	"fsel",		173},
{13,	9,	'I',	4,	"mhri",		115},
{13,	10,	'X',	4,	"rldcl",	120},
{13,	11,	'X',	4,	"rldcr",	121},
{13,	12,	'X',	4,	"lrdic",	119},
{13,	13,	'X',	4,	"rldicl",	118},
{13,	14,	'X',	4,	"rldicr",	118},
{14,	0,	'D',	5,	"stw",		60},
{14,	1,	'D',	5,	"stwc",		77},
{14,	2,	'D',	5,	"stfd",		64},
{14,	3,	'D',	5,	"stqh",		60},
{14,	4,	'D',	5,	"sth",		59},
{14,	5,	'D',	5,	"stwbr",	66},
{14,	6,	'D',	5,	"stfs",		64},
{14,	7,	'D',	5,	"stb",		59},
{14,	8,	'D',	5,	"stsd",		71},
{14,	9,	'D',	5,	"stsw",		71},
{14,	10,	'D',	5,	"stql",		60},
{14,	11,	'D',	5,	"stdc",		78},

{14,	12,	'D',	5,	"sthbr",	66},
{14,	13,	'D',	5,	"std",		60},
{14,	14,	'D',	5,	"addai",	97},
{14,	15,	'I',	5,	"addbi",	93},
{14,	16,	'I',	5,	"andbi",	110},
{14,	17,	'I',	5,	"xorbi",	111},
{14,	18,	'I',	5,	"orbi",		111},
{14,	30,	'B',	8,	"br",		48},
{14,	62,	'I',	8,	"eiu",		86},
{15,	0,	'I',	6,	"csxr",		91},
{15,	1,	'I',	6,	"csfr",		91},
{15,	2,	'X',	6,	"orc",		113},
{15,	3,	'X',	6,	"sraw",		126},
{15,	4,	'X',	6,	"or",		112},
{15,	5,	'X',	6,	"subf",		94},
{15,	6,	'X',	6,	"eqv",		113},
{15,	7,	'X',	6,	"sradi",	124},
{15,	8,	'X',	6,	"srad",		125},
{15,	9,	'X',	6,	"subfc",	95},
{15,	10,	'X',	6,	"subfe",	96},
{15,	11,	'X',	6,	"slw",		123},
{15,	12,	'X',	6,	"sld",		122},
{15,	13,	'X',	6,	"srw",		124},
{15,	14,	'X',	6,	"xor",		112},
{15,	15,	'X',	6,	"add",		93},
{15,	16,	'X',	6,	"and",		112},
{15,	17,	'X',	6,	"andc",		113},
{15,	18,	'X',	6,	"nor",		113},
{15,	19,	'X',	6,	"nand",		112},
{15,	20,	'X',	6,	"srd",		123},
{15,	21,	'X',	6,	"srawi",	125},
{15,	22,	'X',	6,	"adde",		95},
{15,	23,	'X',	6,	"addc",		94},
{15,	24,	'X',	6,	"asldi",	127},
{15,	25,	'X',	6,	"aslwi",	127},
{15,	26,	'X',	6,	"sldia",	127},
{15,	27,	'X',	6,	"slwia",	127},
{15,	28,	'X',	6,	"sradia",	128},
{15,	29,	'X',	6,	"srawia",	128},
{15,	30,	'X',	6,	"asradi",	128},
{15,	31,	'X',	6,	"asrawi",	128}
};

int for_ops_elem = sizeof (for_ops) / sizeof (for_ops[0]);

OPCODE *for_ops_sort[sizeof (for_ops) / sizeof (for_ops[0])];
