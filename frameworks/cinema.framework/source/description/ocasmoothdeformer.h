#ifndef OCASMOOTHDEFORMER_H__
#define OCASMOOTHDEFORMER_H__

enum
{
	ID_CA_SMOOTHING_DEFORMER_OBJECT_ITERATIONS = 1000,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_STIFFNESS,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_STRENGTH,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_TYPE,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_INITIAL,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_MEM,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_RESTORE,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_DELTA_LOCK,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_STIFF_MAP,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_SMOOTHING_DEFORMER_OBJECT_TYPE_RELAX = 0,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_TYPE_SMOOTH,
	ID_CA_SMOOTHING_DEFORMER_OBJECT_TYPE_STRETCH,

	ID_CA_SMOOTHING_DEFORMER_OBJECT_DUMMY
};

#endif // OCASMOOTHDEFORMER_H__
