CONTAINER Fsmdloader
{
    NAME Fsmdloader;
    
    GROUP
    {
        GROUP
        {
            NAME S_GENERAL;
            DEFAULT 1;

            BOOL SMD_LOADER_IMPORT_UNDER_NULL {}
        }

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
            NAME S_IMPORT_OPTIONS;
            DEFAULT 1;

            BOOL SMD_LOADER_IMPORT_ANIMATION {}
            BOOL SMD_LOADER_IMPORT_MESH {}
            BOOL SMD_LOADER_IMPORT_WEIGHTS {}
        }
    }
}