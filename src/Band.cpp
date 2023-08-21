#include "Band.h"

Band::Band(BandId bandId, unsigned int lowFreqHz, unsigned int highFreqHz) {
    this->id = bandId;
    this->lowestFreqHz = lowFreqHz;
    this-> highestFreqHz = highFreqHz;
}

bool Band::frequencyInBand(unsigned int freq, FrequencyUnit unit) const {
    //Based on the unit, mask out unknown frequency positions
    unsigned int _lowFreqToCompare = this->lowestFreqHz;
    unsigned int _highFreqToCompare = this->highestFreqHz;
    
    //Division between integers. Reminder will be just discarded.
    //Last multiplication fills with zeros.
    _lowFreqToCompare = (_lowFreqToCompare / unit ) * unit;
    _highFreqToCompare = (_highFreqToCompare / unit ) * unit;

    return _lowFreqToCompare <= freq && 
        freq <= _highFreqToCompare;
}

BandId Band::getBandId() const {
    return this->id;
}

FrequencyUnit Band::getFrequencyUnitFromTenExponent(unsigned char tenExp) {
    switch(tenExp) {
        default:
        case 0:
            return HZ;
        case 1:
            return DECA_HZ;
        case 2:
            return HECTO_HZ;
        case 3:
            return KILO_HZ;
        case 4:
            return MYRIA_HZ;
        case 5:
            return HECTOKILO_HZ;
        case 6:
            return MEGA_HZ;
        case 7:
            return HEBDO_HZ;
    }
}