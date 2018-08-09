

typedef	unsigned short typCUR[256];
typedef	unsigned short typICON[256];

typedef struct 
{
    typCUR	cursorbits,
    		cursormbits;
	typICON	lbits,
			lmbits,
			cbits,
			cmbits,
			rbits,
			rmbits,
			s1bits,
			s1mbits,
			s1mpbits,
			s1pbits,
			s2bits,
			s2mbits,
			s2mpbits,
			s2pbits,
			s3bits,
			s3mbits,
			s3mpbits,
			s3pbits,
			s4bits,
			s4mbits,
			s4mpbits,
			s4pbits,
			s5bits,
			s5mbits,
			s5mpbits,
			s5pbits,
			s6bits,
			s6mbits,
			s6mpbits,
			s6pbits;
            int             iconxhot;
            int             iconyhot;
            unsigned long   iconfg;
            unsigned long   iconbg;
			char			warSound[6][BUFSIZ];
} typICONSET;

static typICONSET icons[] =
{
    {
        {
#include "icons/sentrycursor.icon"
        },
        {
#include "icons/sentrycursorm.icon"
        },
        {
#include "icons/sentryl.icon"
        },
        {
#include "icons/sentrylm.icon"
        },
        {
#include "icons/sentryc.icon"
        },
        {
#include "icons/sentrycm.icon"
        },
        {
#include "icons/sentryr.icon"
        },
        {
#include "icons/sentryrm.icon"
        },
        {
#include "icons/sentrys1.icon"
        },
        {
#include "icons/sentrys1m.icon"
        },
        {
#include "icons/sentrys1mp.icon"
        },
        {
#include "icons/sentrys1p.icon"
        },
        {
#include "icons/sentrys2.icon"
        },
        {
#include "icons/sentrys2m.icon"
        },
        {
#include "icons/sentrys2mp.icon"
        },
        {
#include "icons/sentrys2p.icon"
        },
        {
#include "icons/sentrys3.icon"
        },
        {
#include "icons/sentrys3m.icon"
        },
        {
#include "icons/sentrys3mp.icon"
        },
        {
#include "icons/sentrys3p.icon"
        },
        {
#include "icons/sentrys4.icon"
        },
        {
#include "icons/sentrys4m.icon"
        },
        {
#include "icons/sentrys4mp.icon"
        },
        {
#include "icons/sentrys4p.icon"
        },
        {
#include "icons/sentrys5.icon"
        },
        {
#include "icons/sentrys5m.icon"
        },
        {
#include "icons/sentrys5mp.icon"
        },
        {
#include "icons/sentrys5p.icon"
        },
        {
#include "icons/sentrys6.icon"
        },
        {
#include "icons/sentrys6m.icon"
        },
        {
#include "icons/sentrys6mp.icon"
        },
        {
#include "icons/sentrys6p.icon"
        },
    },
    {
        {
#include "icons/boatcursor.icon"
        },
        {
#include "icons/boatcursorm.icon"
        },
        {
#include "icons/boatl.icon"
        },
        {
#include "icons/boatlm.icon"
        },
        {
#include "icons/boatc.icon"
        },
        {
#include "icons/boatcm.icon"
        },
        {
#include "icons/boatr.icon"
        },
        {
#include "icons/boatrm.icon"
        },
        {
#include "icons/boats1.icon"
        },
        {
#include "icons/boats1m.icon"
        },
        {
#include "icons/boats1mp.icon"
        },
        {
#include "icons/boats1p.icon"
        },
        {
#include "icons/boats2.icon"
        },
        {
#include "icons/boats2m.icon"
        },
        {
#include "icons/boats2mp.icon"
        },
        {
#include "icons/boats2p.icon"
        },
        {
#include "icons/boats3.icon"
        },
        {
#include "icons/boats3m.icon"
        },
        {
#include "icons/boats3mp.icon"
        },
        {
#include "icons/boats3p.icon"
        },
        {
#include "icons/boats4.icon"
        },
        {
#include "icons/boats4m.icon"
        },
        {
#include "icons/boats4mp.icon"
        },
        {
#include "icons/boats4p.icon"
        },
        {
#include "icons/boats5.icon"
        },
        {
#include "icons/boats5m.icon"
        },
        {
#include "icons/boats5mp.icon"
        },
        {
#include "icons/boats5p.icon"
        },
        {
#include "icons/boats6.icon"
        },
        {
#include "icons/boats6m.icon"
        },
        {
#include "icons/boats6mp.icon"
        },
        {
#include "icons/boats6p.icon"
        },
    },
    {
        {
#include "icons/dogcursor.icon"
        },
        {
#include "icons/dogcursorm.icon"
        },
        {
#include "icons/dogl.icon"
        },
        {
#include "icons/doglm.icon"
        },
        {
#include "icons/dogc.icon"
        },
        {
#include "icons/dogcm.icon"
        },
        {
#include "icons/dogr.icon"
        },
        {
#include "icons/dogrm.icon"
        },
        {
#include "icons/dogs1.icon"
        },
        {
#include "icons/dogs1m.icon"
        },
        {
#include "icons/dogs1mp.icon"
        },
        {
#include "icons/dogs1p.icon"
        },
        {
#include "icons/dogs2.icon"
        },
        {
#include "icons/dogs2m.icon"
        },
        {
#include "icons/dogs2mp.icon"
        },
        {
#include "icons/dogs2p.icon"
        },
        {
#include "icons/dogs3.icon"
        },
        {
#include "icons/dogs3m.icon"
        },
        {
#include "icons/dogs3mp.icon"
        },
        {
#include "icons/dogs3p.icon"
        },
        {
#include "icons/dogs4.icon"
        },
        {
#include "icons/dogs4m.icon"
        },
        {
#include "icons/dogs4mp.icon"
        },
        {
#include "icons/dogs4p.icon"
        },
        {
#include "icons/dogs5.icon"
        },
        {
#include "icons/dogs5m.icon"
        },
        {
#include "icons/dogs5mp.icon"
        },
        {
#include "icons/dogs5p.icon"
        },
        {
#include "icons/dogs6.icon"
        },
        {
#include "icons/dogs6m.icon"
        },
        {
#include "icons/dogs6mp.icon"
        },
        {
#include "icons/dogs6p.icon"
        },
    },
    {
        {
#include "icons/trekcursor.icon"
        },
        {
#include "icons/trekcursorm.icon"
        },
        {
#include "icons/trekl.icon"
        },
        {
#include "icons/treklm.icon"
        },
        {
#include "icons/trekc.icon"
        },
        {
#include "icons/trekcm.icon"
        },
        {
#include "icons/trekr.icon"
        },
        {
#include "icons/trekrm.icon"
        },
        {
#include "icons/treks1.icon"
        },
        {
#include "icons/treks1m.icon"
        },
        {
#include "icons/treks1mp.icon"
        },
        {
#include "icons/treks1p.icon"
        },
        {
#include "icons/treks2.icon"
        },
        {
#include "icons/treks2m.icon"
        },
        {
#include "icons/treks2mp.icon"
        },
        {
#include "icons/treks2p.icon"
        },
        {
#include "icons/treks3.icon"
        },
        {
#include "icons/treks3m.icon"
        },
        {
#include "icons/treks3mp.icon"
        },
        {
#include "icons/treks3p.icon"
        },
        {
#include "icons/treks4.icon"
        },
        {
#include "icons/treks4m.icon"
        },
        {
#include "icons/treks4mp.icon"
        },
        {
#include "icons/treks4p.icon"
        },
        {
#include "icons/treks5.icon"
        },
        {
#include "icons/treks5m.icon"
        },
        {
#include "icons/treks5mp.icon"
        },
        {
#include "icons/treks5p.icon"
        },
        {
#include "icons/treks6.icon"
        },
        {
#include "icons/treks6m.icon"
        },
        {
#include "icons/treks6mp.icon"
        },
        {
#include "icons/treks6p.icon"
        },
    },
    {
        {
#include "icons/ngtrekcursor.icon"
        },
        {
#include "icons/ngtrekcursorm.icon"
        },
        {
#include "icons/ngtrekl.icon"
        },
        {
#include "icons/ngtreklm.icon"
        },
        {
#include "icons/ngtrekc.icon"
        },
        {
#include "icons/ngtrekcm.icon"
        },
        {
#include "icons/ngtrekr.icon"
        },
        {
#include "icons/ngtrekrm.icon"
        },
        {
#include "icons/ngtreks1.icon"
        },
        {
#include "icons/ngtreks1m.icon"
        },
        {
#include "icons/ngtreks1mp.icon"
        },
        {
#include "icons/ngtreks1p.icon"
        },
        {
#include "icons/ngtreks2.icon"
        },
        {
#include "icons/ngtreks2m.icon"
        },
        {
#include "icons/ngtreks2mp.icon"
        },
        {
#include "icons/ngtreks2p.icon"
        },
        {
#include "icons/ngtreks3.icon"
        },
        {
#include "icons/ngtreks3m.icon"
        },
        {
#include "icons/ngtreks3mp.icon"
        },
        {
#include "icons/ngtreks3p.icon"
        },
        {
#include "icons/ngtreks4.icon"
        },
        {
#include "icons/ngtreks4m.icon"
        },
        {
#include "icons/ngtreks4mp.icon"
        },
        {
#include "icons/ngtreks4p.icon"
        },
        {
#include "icons/ngtreks5.icon"
        },
        {
#include "icons/ngtreks5m.icon"
        },
        {
#include "icons/ngtreks5mp.icon"
        },
        {
#include "icons/ngtreks5p.icon"
        },
        {
#include "icons/ngtreks6.icon"
        },
        {
#include "icons/ngtreks6m.icon"
        },
        {
#include "icons/ngtreks6mp.icon"
        },
        {
#include "icons/ngtreks6p.icon"
        },
    },
    {
        {
#include "icons/tankcursor.icon"
        },
        {
#include "icons/tankcursorm.icon"
        },
        {
#include "icons/tankl.icon"
        },
        {
#include "icons/tanklm.icon"
        },
        {
#include "icons/tankc.icon"
        },
        {
#include "icons/tankcm.icon"
        },
        {
#include "icons/tankr.icon"
        },
        {
#include "icons/tankrm.icon"
        },
        {
#include "icons/tanks1.icon"
        },
        {
#include "icons/tanks1m.icon"
        },
        {
#include "icons/tanks1mp.icon"
        },
        {
#include "icons/tanks1p.icon"
        },
        {
#include "icons/tanks2.icon"
        },
        {
#include "icons/tanks2m.icon"
        },
        {
#include "icons/tanks2mp.icon"
        },
        {
#include "icons/tanks2p.icon"
        },
        {
#include "icons/tanks3.icon"
        },
        {
#include "icons/tanks3m.icon"
        },
        {
#include "icons/tanks3mp.icon"
        },
        {
#include "icons/tanks3p.icon"
        },
        {
#include "icons/tanks4.icon"
        },
        {
#include "icons/tanks4m.icon"
        },
        {
#include "icons/tanks4mp.icon"
        },
        {
#include "icons/tanks4p.icon"
        },
        {
#include "icons/tanks5.icon"
        },
        {
#include "icons/tanks5m.icon"
        },
        {
#include "icons/tanks5mp.icon"
        },
        {
#include "icons/tanks5p.icon"
        },
        {
#include "icons/tanks6.icon"
        },
        {
#include "icons/tanks6m.icon"
        },
        {
#include "icons/tanks6mp.icon"
        },
        {
#include "icons/tanks6p.icon"
        },
    },
    {
        {
#include "icons/defconcursor.icon"
        },
        {
#include "icons/defconcursorm.icon"
        },
        {
#include "icons/defconl.icon"
        },
        {
#include "icons/defconlm.icon"
        },
        {
#include "icons/defconc.icon"
        },
        {
#include "icons/defconcm.icon"
        },
        {
#include "icons/defconr.icon"
        },
        {
#include "icons/defconrm.icon"
        },
        {
#include "icons/defcons1.icon"
        },
        {
#include "icons/defcons1m.icon"
        },
        {
#include "icons/defcons1mp.icon"
        },
        {
#include "icons/defcons1p.icon"
        },
        {
#include "icons/defcons2.icon"
        },
        {
#include "icons/defcons2m.icon"
        },
        {
#include "icons/defcons2mp.icon"
        },
        {
#include "icons/defcons2p.icon"
        },
        {
#include "icons/defcons3.icon"
        },
        {
#include "icons/defcons3m.icon"
        },
        {
#include "icons/defcons3mp.icon"
        },
        {
#include "icons/defcons3p.icon"
        },
        {
#include "icons/defcons4.icon"
        },
        {
#include "icons/defcons4m.icon"
        },
        {
#include "icons/defcons4mp.icon"
        },
        {
#include "icons/defcons4p.icon"
        },
        {
#include "icons/defcons5.icon"
        },
        {
#include "icons/defcons5m.icon"
        },
        {
#include "icons/defcons5mp.icon"
        },
        {
#include "icons/defcons5p.icon"
        },
        {
#include "icons/defcons6.icon"
        },
        {
#include "icons/defcons6m.icon"
        },
        {
#include "icons/defcons6mp.icon"
        },
        {
#include "icons/defcons6p.icon"
        },
    },
};


