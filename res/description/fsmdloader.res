CONTAINER Fsmdloader
{
	NAME Fsmdloader;

	GROUP
	{
		GROUP
		{
			NAME S_SCALEORIENTATION;
			DEFAULT 1;
			REAL SMD_LOADER_SCALE
			{
				MIN 0.01;
				MAX 100;
				STEP 0.1;
			}
		}

		GROUP
		{
			NAME S_IMPORTOPTIONS;
			DEFAULT 1;
			BOOL SMD_IMPORT_ANIMATION {}
			BOOL SMD_IMPORT_MESH {}
		}
	}
}