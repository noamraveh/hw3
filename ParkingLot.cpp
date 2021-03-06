#include "ParkingLot.h"
#include "Vehicle.h"
#include "ParkingLotPrinter.h"

namespace MtmParkingLot {

    //c'tor
    ParkingLot::ParkingLot(unsigned int *parkingBlockSizes) :
            motorbike_parking(parkingBlockSizes[0]),
            handicapped_parking(parkingBlockSizes[1]),
            car_parking(parkingBlockSizes[2]) {
    }

    //findVehicleInBlock

    bool ParkingLot::findVehicleInBlock(
            UniqueArray<Vehicle, VehicleCompare> parking_block,
            Vehicle vehicle) {
        int spot = parking_block.elementExists(vehicle);
        if (spot >= 0) {
            return true;
        }
        return false;
    }

    //findVehicleInLot
    bool ParkingLot::findVehicleInLot(Vehicle vehicle) {
        return ParkingLot::findVehicleInBlock(motorbike_parking, vehicle) ||
               ParkingLot::findVehicleInBlock(car_parking, vehicle) ||
               ParkingLot::findVehicleInBlock(handicapped_parking, vehicle);
    }

    //enter_parking
    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
                                           LicensePlate licensePlate,
                                           Time entranceTime) {
        Vehicle vehicle(vehicleType, licensePlate, entranceTime);
        //parked somewhere in lot
        if (findVehicleInLot(vehicle)) {
            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                              vehicle.getParkingSpot());
            return VEHICLE_ALREADY_PARKED;
        }
        //full/insert
        switch (vehicleType) {
            case MOTORBIKE: {
                return ParkingLot::entryHelper(motorbike_parking, vehicle, MOTORBIKE);
            }
            case CAR: {
                return ParkingLot::entryHelper(car_parking, vehicle, CAR);
            }
            case HANDICAPPED: {
                ParkingResult handicapped_result = ParkingLot::entryHelper(
                        handicapped_parking, vehicle, HANDICAPPED);
                if (handicapped_result == NO_EMPTY_SPOT) {
                    return ParkingLot::entryHelper(car_parking, vehicle, CAR);
                }
                return handicapped_result;
            }
            default:
                break;
        }
        // shouldn't reach here
        return SUCCESS;
    }

    // entryHelper
    ParkingResult ParkingLot::entryHelper(
            UniqueArray<Vehicle, std::equal_to> parking_block,
            Vehicle vehicle, VehicleType parking_block_type) {

        //current block is full
        if (parking_block.getCount() == parking_block.getSize()) {
            if (!(parking_block == handicapped_parking)) {
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
            }
            return NO_EMPTY_SPOT;
        }
        //block is not full
        int index = parking_block.insert(vehicle);
        vehicle.UpdateParkingSpot(parking_block_type, index);
        ParkingLotPrinter::printVehicle(std::cout, vehicle.getVehicleType(),
                                        vehicle.getLicensePlate(),
                                        vehicle.getEntranceTime());
        ParkingLotPrinter::printEntrySuccess(std::cout,
                                             vehicle.getParkingSpot());
        return SUCCESS;
    }



}