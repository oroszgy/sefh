
//filter options
#define FILTER_STEM 0x1L
#define FILTER_STEM_AND_POS 0x2L
#define FILTER_COMPOUND_WORDS 0x4L
#define FILTER_DERIVED_STEMS 0x8L

/*
description:
FILTER_STEM = the same stem will be only once
FILTER_STEM_AND_POS = the same stem+pos will be only once
		for example "ment" has 3 stems: 
			"ment[ige](én vmit)", "megy[IGE](õ)", "ment[MN](vmitõl mentes)"
				with FILTER_STEM output is: 
					"ment,megy"
				with FILTER_STEM_AND_POS output is: 
					"ment,ment,megy"
FILTER_COMPOUND_WORDS = compound words are filtered if there are other alternatives 
		(for example "szer+elem" will be filtered because it has stem "szerelem", too)
FILTER_DERIVED_STEMS = "adós" != "ad", if "adós" is in lexicon
*/

//output display options
#define SHOW_STEM_ONLY 0x10L
#define SHOW_STEM_AND_POS 0x20L
#define SHOW_COMPOUND_POSITIONS 0x40L
#define SHOW_STEM_FULL 0x80L

/*
description:
SHOW_STEM_ONLY = output contains only stems ("alma,alom")
SHOW_STEM_AND_POS = output contains stems and part of speech ("alma[FN],alom[FN]")
SHOW_COMPOUND_POSITIONS = output contains compound delimiter positions ("ablak+kilincs")
SHOW_STEM_FULL = output contains every mophological categories
*/

//other options
#define CASE_SENSITIVE 0x100L
#define COPY_INPUT_CAPITALISATION 0x200L

