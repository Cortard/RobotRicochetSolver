#ifndef TRADUCTIONCPP_SOLVER_H
#define TRADUCTIONCPP_SOLVER_H

#define MAX_DEPTH 32

#define NORTH 0x01
#define EAST  0x02
#define SOUTH 0x04
#define WEST  0x08
#define ROBOT 0x10

#define HAS_WALL(x, wall) (x & wall) // x & wall = 1 si x contient wall
#define HAS_ROBOT(x) (x & ROBOT) // x & ROBOT = 1 si x contient ROBOT (0b00010000)
#define SET_ROBOT(x) (x |= ROBOT) // x |= ROBOT -> x = x | ROBOT -> x = x | 0b00010000
#define UNSET_ROBOT(x) (x &= ~ROBOT) // x &= ~ROBOT -> x = x & ~ROBOT -> x = x & 0b11101111

#define PACK_MOVE(robot, direction) (robot << 4 | direction) // robot << 4 | direction -> 0b00010000 | direction
#define PACK_UNDO(robot, start, last) (robot << 16 | start << 8 | last)
#define UNPACK_ROBOT(undo) ((undo >> 16) & 0xff)
#define UNPACK_START(undo) ((undo >> 8) & 0xff)
#define UNPACK_LAST(undo) (undo & 0xff)
#define MAKE_KEY(x) (x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24))



class solver {

};


#endif //TRADUCTIONCPP_SOLVER_H
