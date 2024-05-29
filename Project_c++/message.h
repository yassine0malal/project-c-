#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

// message.h  :  fonctions pour 'affichage des messages d'erreur
//              et une fonction supplémentaire pour indiquer le succès de la lecture
//
// public version V1
//

#include <string>

namespace message
{
	// age must be strictly positive
	std::string lifeform_age(unsigned );

	// only for the center coordinate that are explicitely visible in the file
	// allowed interval is [1, max-1]
	std::string lifeform_center_outside(double , double );

	// only for the inner rotation center and the extremity that have to be computed.
	// allowed interval is ]0, max[
	// use the lifeform_center_outside as message for the corail origin
	std::string lifeform_computed_outside(unsigned , double , double );

	std::string segment_length_outside(unsigned , unsigned );

	std::string segment_angle_outside(unsigned , double );

	std::string scavenger_radius_outside(unsigned );

	std::string lifeform_duplicated_id(unsigned );

	std::string lifeform_invalid_id(unsigned );

	// as suggested by their name the segment index values start at zero
	std::string segment_collision(unsigned , unsigned ,
								  unsigned , unsigned );

	// only for the case of 2 consecutive segments
	std::string segment_superposition(unsigned , unsigned , unsigned );

	// Everything went well => file reading and all validation checks
	std::string success();
}

#endif // MESSAGE_H_INCLUDED
