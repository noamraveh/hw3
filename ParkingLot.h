#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "Vehicle.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
        //change to compare
        UniqueArray<Vehicle,std::equal_to> motorbike_parking;
        UniqueArray<Vehicle,std::equal_to> handicapped_parking;
        UniqueArray<Vehicle,std::equal_to> car_parking;

    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        bool findVehicleInLot (Vehicle vehicle);
        bool findVehicleInBlock (UniqueArray<Vehicle,VehicleCompare> parking_block, Vehicle vehicle);
        ParkingResult entryHelper (
                UniqueArray<Vehicle, std::equal_to> parking_block,
                Vehicle vehicle,
                VehicleType parking_block_type);
    };

    enum parking_block {
        motorbike_parking = 0;
        handicapped_parking;
        car_parking;
    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
