#ifndef BAND_H
#define BAND_H

#define M_40_MIN_FREQ 7000000
#define M_40_MAX_FREQ 7200000
#define M_30_MIN_FREQ 10100000
#define M_30_MAX_FREQ 10150000
#define M_20_MIN_FREQ 14000000
#define M_20_MAX_FREQ 14350000
#define M_17_MIN_FREQ 18068000
#define M_17_MAX_FREQ 18168000
#define M_15_MIN_FREQ 21000000
#define M_15_MAX_FREQ 21450000
#define M_12_MIN_FREQ 24890000
#define M_12_MAX_FREQ 24990000
#define M_10_MIN_FREQ 28000000
#define M_10_MAX_FREQ 29700000

enum Modulation {
    USB, LSB
};

//Frequency is represented in Hertz and goes up to 30 megahertz
//Max frequency is 29.700.000 hertz
#define DIGITS_IN_FREQUENCY 8
#define MAX_TEN_EXP_FOR_FREQUENCY 7

enum FrequencyUnit : unsigned int {
    HZ              = 1,        //10^0
    DECA_HZ         = 10,       //10^1
    HECTO_HZ        = 100,      //10^2
    KILO_HZ         = 1000,     //10^3
    MYRIA_HZ        = 10000,    //10^4
    HECTOKILO_HZ    = 100000,   //10^5
    MEGA_HZ         = 1000000,  //10^6
    HEBDO_HZ        = 10000000  //10^7
};

enum BandId {
    M_40 = 40,
    M_30 = 30,
    M_20 = 20,
    M_17 = 17,
    M_15 = 15,
    M_12 = 12,
    M_10 = 10,
    NONE = 0
};

class Band {

public:
    Band(BandId bandId, unsigned int lowFreqHz, unsigned int highFreqHz);
    bool frequencyInBand(unsigned int freq, FrequencyUnit unit) const;

    /* Example: if ten exponent is 3 => 10^3 => returns KILO_HZ */
    static FrequencyUnit getFrequencyUnitFromTenExponent(unsigned char tenExp);
    BandId getBandId() const;
    
private:
    unsigned int lowestFreqHz;
    unsigned int highestFreqHz;
    BandId id;
};

#endif