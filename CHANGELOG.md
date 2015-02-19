attr changelog

Version 1.4 - 28 Feb 07:

	Enabled -n | --not-indexed + | -  Set/reset content not indexed bit
	Enabled -o | --offline     + | -  Set/reset offline bit
	Enabled -t | --temporary   + | -  Set/reset temporary bit

Version 1.3 - 14 Nov 06:

	Added display of attributes in the form 'arhsnot'
	Added -d | --directories        Set/reset bits on directories
	Added -y | --dry-run            Change nothing, just report what would change
	Added -i | --hide-attributes    Do not show attributes
	Improved error handling
	Processes *.* if no filespec is specified
	Return errorcode if an error occured (and --abort-on-error is set)
	Report on changed files only (unless -v is used)
	Skipped processing of . and .. directories

Version 1.2 - 19 Jul 06:

	Standardized version information across all programs

Version 1.1 - 08 Apr 06:

	Added -n | --not-indexed + | -  Set/reset content not indexed bit
	Added -o | --offline     + | -  Set/reset offline bit
	Added -t | --temporary   + | -  Set/reset temporary bit
	Added -e | --abort-on-error     Abort if an error occurs
	Added .rc and .ico files
	Improved build scripts
	Updated documentation
	
Version 1.0 - 12 Apr 04:

	Initial release
