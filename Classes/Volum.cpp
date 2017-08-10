#include "Volum.h"

VolumSet* VolumSet::instance = NULL;
VolumSet* VolumSet::getInstance()
{
	if (instance == NULL)
		instance = new VolumSet();
	return instance;
}