set(PACKAGE_VERSION )
if(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)
    set(PACKAGE_VERSION_COMPATIBLE FALSE)
else(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
    if(PACKAGE_VERSION VERSION_EQUAL PACKAGE_FIND_VERSION)
        set(PACKAGE_VERSION_EXACT TRUE)
    endif(PACKAGE_VERSION VERSION_EQUAL PACKAGE_FIND_VERSION)
endif(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)

