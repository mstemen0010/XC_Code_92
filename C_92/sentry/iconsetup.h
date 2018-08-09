#define CURSORSIZ 1024
#define ICONSIZ 4096

typedef struct {
	unsigned short cursor_bits[CURSORSIZ];
	unsigned short cursorm_bits[CURSORSIZ];
	unsigned short l_bits[ICONSIZ];         /* left pose */
	unsigned short lm_bits[ICONSIZ];
	unsigned short r_bits[ICONSIZ];         /* right pose */
	unsigned short rm_bits[ICONSIZ];
	unsigned short c_bits[ICONSIZ];         /* center pose */
	unsigned short cm_bits[ICONSIZ];
	unsigned short s1_bits[ICONSIZ];        /* siege phase 1 1st pose */
	unsigned short s1m_bits[ICONSIZ];
	unsigned short s2_bits[ICONSIZ];        /* siege phase 2 1st pose */
	unsigned short s2m_bits[ICONSIZ];
	unsigned short s3_bits[ICONSIZ];        /* siege phase 3 1st pose */
	unsigned short s3m_bits[ICONSIZ];
	unsigned short s4_bits[ICONSIZ];        /* siege phase 4 1st pose */
	unsigned short s4m_bits[ICONSIZ];
	unsigned short s5_bits[ICONSIZ];        /* siege phase 5 1st pose */
	unsigned short s5m_bits[ICONSIZ];
	unsigned short s6_bits[ICONSIZ];        /* siege phase 6 1st pose */
	unsigned short s6m_bits[ICONSIZ];
	unsigned short s1p_bits[ICONSIZ];       /* siege phase 1 2nd pose */
	unsigned short s1mp_bits[ICONSIZ];
	unsigned short s2p_bits[ICONSIZ];       /* siege phase 2 2nd pose */
	unsigned short s2mp_bits[ICONSIZ];
	unsigned short s3p_bits[ICONSIZ];       /* siege phase 3 2nd pose */
	unsigned short s3mp_bits[ICONSIZ];
	unsigned short s4p_bits[ICONSIZ];       /* siege phase 4 2nd pose */
	unsigned short s4mp_bits[ICONSIZ];
	unsigned short s5p_bits[ICONSIZ];       /* siege phase 5 2nd pose */
	unsigned short s5mp_bits[ICONSIZ];
	unsigned short s6p_bits[ICONSIZ];       /* siege phase 6 2nd pose */
	unsigned short s6mp_bits[ICONSIZ];
} ICONSETUP;

/* Now lets declare 3 sets of icons groups 
iconset[0] will be the tower set
iconset[1] will be the dog set
iconset[2] will be the defcon set
*/

ICONSETUP iconset[2];
