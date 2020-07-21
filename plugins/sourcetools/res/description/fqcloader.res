CONTAINER Fqcloader
{
    NAME Fqcloader;

    GROUP
    {
        GROUP
        {
            NAME S_GENERAL;
            DEFAULT 1;

            BOOL QC_LOADER_IMPORT_UNDER_NULL {}
        }

        GROUP
        {
            NAME S_SCALEORIENTATION;
            DEFAULT 1;

            REAL QC_LOADER_SCALE
            {
                MIN 0.01;
                MAX 100;
                STEP 0.1;
            }

            VECTOR QC_LOADER_ROTATE { UNIT DEGREE; }
        }

        GROUP
        {
            NAME S_IMPORT_OPTIONS;
            DEFAULT 1;

            BOOL QC_LOADER_IMPORT_SKELETON {}
            BOOL QC_LOADER_IMPORT_MESH {}
            BOOL QC_LOADER_IMPORT_WEIGHTS {}
            BOOL QC_LOADER_IMPORT_MATERIALS {}
            FILENAME QC_LOADER_MATERIAL_PATH { DIRECTORY; }
        }
    }
}