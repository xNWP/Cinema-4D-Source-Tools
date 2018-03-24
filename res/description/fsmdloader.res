CONTAINER Fsmdloader
{
	NAME Fsmdloader;

	GROUP
	{
		STRING SMD_CUSTOM_ROOT_NAME { HIDDEN; }

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

			VECTOR SMD_LOADER_ROTATE { UNIT DEGREE; }
		}

		GROUP
		{
			NAME S_IMPORTOPTIONS;
			DEFAULT 1;
			LAYOUTGROUP; COLUMNS 2;

			GROUP
			{
				BOOL SMD_IMPORT_ANIMATION {}
				BOOL SMD_IMPORT_MESH {}
				BOOL SMD_IMPORT_QC {}
			}

			GROUP
			{
				BOOL SMD_IMPORT_TOP_NULL {}
				BOOL SMD_IMPORT_SKELETON_JOINT {}
			}
		}

		GROUP
		{
			NAME S_MESH;
			DEFAULT 1;
			LAYOUTGROUP;
			COLUMNS 2;

			GROUP
			{
				BOOL SMD_IMPORT_MESH_WELD {}
				BOOL SMD_IMPORT_MESH_NORMALS {}
				BOOL SMD_IMPORT_MESH_MATERIALS {}
			}
			
			GROUP
			{
				REAL SMD_IMPORT_MESH_WELD_TOLERANCE
				{
					MIN 0.001;
					MAX 10;
					STEP 0.01;
				}
				BOOL SMD_IMPORT_MESH_UV {}
				BOOL SMD_IMPORT_MESH_WEIGHTS {}
			}
		}

		GROUP
		{
			NAME S_QC;
			DEFAULT 1;

			FILENAME SMD_IMPORT_MATERIAL_ROOT { DIRECTORY; }
			
			SEPARATOR {}

			BOOL SMD_IMPORT_IK {}
			LONG SMD_IMPORT_IK_ORIENTATION
			{
				PARENTID SMD_IMPORT_IK;
				CYCLE
				{
					IK_CAMERA;
					IK_XY;
					IK_ZY;
					IK_XZ;
				}
			}
		}

		GROUP
		{
			NAME S_MEMORY;

			BOOL SMD_CACHE_MEMORY {};

			SEPARATOR {}

			STATICTEXT SMD_MEMORY_USAGE {};
			BUTTON SMD_FLUSH_CACHE {};
		}
	}
}