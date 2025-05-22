# Findlibmicrohttpd.cmake

# Define the minimum required version (adjust if needed)
if(NOT libmicrohttpd_FIND_VERSION)
	  set(libmicrohttpd_FIND_VERSION "0.9.0")  # Example; set based on your version
  endif()

  # Search for the library in the specified path
  find_path(LIBMHD_INCLUDE_DIR
	            NAMES microhttpd.h
		              HINTS ${libmicrohttpd_ROOT}  # This will be set to your build directory
			                PATH_SUFFIXES include src/include)

				find_library(LIBMHD_LIBRARY
					             NAMES microhttpd libmicrohttpd
						                  HINTS ${libmicrohttpd_ROOT}
								               PATH_SUFFIXES src/.libs .libs lib)

								       # Handle the results
								       include(FindPackageHandleStandardArgs)
								       find_package_handle_standard_args(libmicrohttpd
									                                         REQUIRED_VARS LIBMHD_LIBRARY LIBMHD_INCLUDE_DIR
														                                   VERSION_VAR libmicrohttpd_VERSION)

																	   if(libmicrohttpd_FOUND)
																		     set(LIBMHD_LIBRARIES ${LIBMHD_LIBRARY})
																		       set(LIBMHD_INCLUDE_DIRS ${LIBMHD_INCLUDE_DIR})
																		         message(STATUS "Found libmicrohttpd: ${LIBMHD_LIBRARIES}")
																		 else()
																			   message(FATAL_ERROR "libmicrohttpd not found. Set libmicrohttpd_ROOT to your build directory.")
																		   endif()

																		   mark_as_advanced(LIBMHD_INCLUDE_DIRS LIBMHD_LIBRARIES)
