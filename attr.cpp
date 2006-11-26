/*

$Id$

Copyright (c) 2004-2006 Ross Smith II (http://smithii.com). All rights reserved.

This program is free software; you can redistribute it and/or modify it
under the terms of version 2 of the GNU General Public License
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

*/

/*
TODO:
If user has admin rights
and setting attribute flag fails
then grant rights
reset bit
revoke rights
*/

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <cstdio>
#include <iostream>
#include <string>

#include <list>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <sys/stat.h> // stat()

#include <io.h>

#include "getopt.h"
#include "version.h"

#define APPNAME			VER_INTERNAL_NAME
#define APPVERSION		VER_STRING2
#define APPCOPYRIGHT	VER_LEGAL_COPYRIGHT

using namespace std;

static char *progname = APPNAME;

static char *short_options = "a:deh:in:o:qr:s:t:vyVR?";

static struct option long_options[] = {
  {"abort-on-error",	no_argument,		0, 'e'},
  {"archive",			required_argument,	0, 'a'},
  {"directories",		no_argument,		0, 'd'},
  {"dry-run",			no_argument,		0, 'y'},
  {"help",				no_argument,		0, '?'},
  {"hidden",			required_argument,	0, 'h'},
  {"hide-attributes",	no_argument,		0, 'i'},
  {"not-indexed",		required_argument,	0, 'n'},
  {"offline",			required_argument,	0, 'o'},
  {"quiet",				no_argument,		0, 'q'},
  {"readonly",			required_argument,	0, 'r'},
  {"recursive",			no_argument,		0, 'R'},
  {"system",			required_argument,	0, 's'},
  {"temporary",			required_argument,	0, 't'},
  {"verbose",			no_argument,		0, 'v'},
  {"version",			no_argument,		0, 'V'},
  {NULL,				0,					0, 0}
};

void usage() {
	cout << "Usage: " << progname <<
		" [options] filespec [filespec]\n\n"
		"Options:\n"
		"-a | --archive     + | -  Set/reset archive bit\n"
		"-r | --readonly    + | -  Set/reset read only bit\n"
		"-h | --hidden      + | -  Set/reset hidden bit\n"
		"-s | --system      + | -  Set/reset system bit\n"
		"-n | --not-indexed + | -  Set/reset content not indexed bit\n"
		"-o | --offline     + | -  Set/reset offline bit\n"
		"-t | --temporary   + | -  Set/reset temporary bit\n"
		"-d | --directories        Set/reset bits on directories\n"
		"-y | --dry-run            Change nothing, just report what would change\n"
		"-i | --hide-attributes    Do not show attributes\n"
		"-e | --abort-on-error     Abort if an error occurs\n"
		"-R | --recursive          Scan directories recursively\n"
		"-q | --quiet              Display less information\n"
		"-v | --verbose            Display more information\n"
		"-V | --version            Show version and copyright information and quit\n"
		"-? | --help               Show this help message and quit\n";
}

typedef enum { OPTION_NO_CHANGE, OPTION_ON, OPTION_OFF } Flag;

struct _opt {
	Flag	archive;
	Flag	hidden;
	Flag	readonly;
	Flag	system;
	Flag	not_indexed;
	Flag	offline;
	Flag	temporary;
	bool	directories;
	bool	dry_run;
	bool	abort;
	bool	hide;
	bool	recursive;
	int		verbose;
};

typedef struct _opt t_opt;

static t_opt opt = {
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	OPTION_NO_CHANGE,
	false,
	false,
	false,
	false,
	false,
	1	/* report on changed files only */
};

/****************************************************************************/
#ifndef HAVE_BASENAME
/****************************************************************************/

/* per http://www.scit.wlv.ac.uk/cgi-bin/mansec?3C+basename */
static char* basename(char* s) {
	char* rv;

	if (!s || !*s)
		return ".";

	rv = s + strlen(s) - 1;

	do {
		if (*rv == '/' || *rv == '\\')
			return rv + 1;
		--rv;
	} while (rv >= s);

	return s;
}

#define HAVE_BASENAME 1

#endif /* ! HAVE_BASENAME */

bool is_directory(const string path) {
  struct stat buf;

  if (path.length())
    if (stat(path.c_str(), &buf) == 0)
      return (buf.st_mode & S_IFDIR) == S_IFDIR;
  return false;
}

void WARNING(string msg) {
	cerr << progname << ": " << msg << endl;
}

void FATAL(string msg) {
	WARNING(msg);
	exit(1);
}

string last_error() {
  int last_error = GetLastError();
  static char buf[2048];
  if (FormatMessage(
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    last_error,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &buf,
    sizeof(buf),
    NULL
    ) == 0) {
      _snprintf(buf, sizeof(buf), "Unknown Windows error %d", last_error);
  }
  return buf;
}

typedef list<string> StringList;

void set_attribute(Flag option, DWORD *attributes, int bit, char *bit_str, int bit_pos, char bit_chr) {
	switch (option) {
		case OPTION_OFF:
			if ((*attributes & bit) == bit) {
				*attributes &= ~bit;
				bit_str[bit_pos] = '_';
			}

			break;
		case OPTION_ON:
			if ((*attributes & bit) != bit) {
				*attributes |= bit;
				bit_str[bit_pos] = toupper(bit_chr);
			} else
				bit_str[bit_pos] = bit_chr;
			break;
		default:
			if (*attributes & bit)
				bit_str[bit_pos] = bit_chr;
	}
}

int do_files(string path, const string filespec) {
	list<string> directories;

	WIN32_FIND_DATA FindFileData;

	if (path.length() > 0) {
		string last_char = path.substr(path.length() - 1, 1);
		if (last_char != "\\" && last_char != "/") {
			path += "\\";
		}
	}

	string temppath = path + filespec;

	HANDLE hFind = ::FindFirstFile(temppath.c_str(), &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		int rv = ::GetLastError();
		WARNING(path + ": " + last_error());
		return rv;
	}

	bool retval = true;

	char bit_str[8];

	bit_str[7] = '\0';

	while (retval) {
		while (true) {
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0) {
					break;
				}
				directories.push_back(FindFileData.cFileName);
				if (!opt.directories) {
					break;
				}
			}

			DWORD attributes = FindFileData.dwFileAttributes;

			for (int i = 0; i < sizeof(bit_str) - 1; ++i) {
				bit_str[i] = '-';
			}

			set_attribute(opt.archive,		&attributes, FILE_ATTRIBUTE_ARCHIVE,				bit_str, 0, 'a');
			set_attribute(opt.readonly,		&attributes, FILE_ATTRIBUTE_READONLY,				bit_str, 1, 'r');
			set_attribute(opt.hidden,		&attributes, FILE_ATTRIBUTE_HIDDEN,					bit_str, 2, 'h');
			set_attribute(opt.system,		&attributes, FILE_ATTRIBUTE_SYSTEM,					bit_str, 3, 's');
			set_attribute(opt.not_indexed,	&attributes, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,	bit_str, 4, 'n');
			set_attribute(opt.offline,		&attributes, FILE_ATTRIBUTE_OFFLINE,				bit_str, 5, 'o');
			set_attribute(opt.temporary,	&attributes, FILE_ATTRIBUTE_TEMPORARY,				bit_str, 6, 't');

			string fullname = path + FindFileData.cFileName;

			if (opt.verbose > 1) {
				if (!opt.hide)
					cout << bit_str << ": ";
				cout << fullname << endl;
			}

			if (attributes != FindFileData.dwFileAttributes) {
				if (opt.verbose == 1) {
					if (!opt.hide)
						cout << bit_str << ": ";
					cout << fullname << endl;
				}

				if (!opt.dry_run && !SetFileAttributes(fullname.c_str(), attributes)) {
					if (opt.abort)
						return GetLastError();
					WARNING(fullname + ": " + last_error());
				}
			}
			break;
		}

		retval = FindNextFile(hFind, &FindFileData) != 0;
		if (!retval && GetLastError() != ERROR_NO_MORE_FILES) {
			WARNING(last_error());
		}
	}

    FindClose(hFind);

	if (!opt.recursive)
		return 0;

	directories.sort();

	for (StringList::iterator it = directories.begin(); it != directories.end(); ++it) {
		string newdir = path + *it;
		do_files(newdir, filespec);
	}

	return 0;
}

static bool set_flag(Flag *flag, const char *optarg) {
	if (strcmp(optarg, "+") == 0) {
		*flag = OPTION_ON;
		return true;
	}
	if (strcmp(optarg, "-") == 0) {
		*flag = OPTION_OFF;
		return true;
	}
	return false;
}

int main(int argc, char **argv) {
	progname = basename(argv[0]);

	if (progname) {
		int len = strlen(progname);
		if (len > 4 && _stricmp(progname + len - 4, ".exe") == 0)
			progname[len - 4] = '\0';
	}

	opterr = 0;
	int option_index = 0;

	while (true) {
		if (optind < argc && argv[optind] && argv[optind][0] == '/')
			argv[optind][0] = '-';

		int c = getopt_long(argc, argv, short_options, long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 'a':
				if (!set_flag(&opt.archive, optarg)) {
					usage();
					exit(1);
				}
				break;
			case 'd':
				opt.directories = true;
				break;
			case 'e':
				opt.abort = true;
				break;
			case 'i':
				opt.hide = true;
				break;
			case 'h':
				if (!set_flag(&opt.hidden, optarg)) {
					usage();
					exit(1);
				}
				break;
			case 'r':
				if (!set_flag(&opt.readonly, optarg)) {
					usage();
					exit(1);
				}
				break;
			case 's':
				if (!set_flag(&opt.system, optarg)) {
					usage();
					exit(1);
				}
				break;
			case 'q':
				if (opt.verbose > 0)
					--opt.verbose;
				break;
			case 'v':
				++opt.verbose;
				break;
			case 'y':
				opt.dry_run = true;
				break;
			case 'R':
				opt.recursive = true;
				break;
			case 'V':
				cout <<
					APPNAME " " APPVERSION " - " __DATE__ << endl <<
					APPCOPYRIGHT << endl;
				break;
			case '?':
				usage();
				break;
			default:
				cerr << "Invalid option: " << optarg << endl;
				usage();
				exit(1);
		}
	}

/*
	if (opt.archive == OPTION_NO_CHANGE &&
		opt.readonly == OPTION_NO_CHANGE &&
		opt.hidden == OPTION_NO_CHANGE &&
		opt.system == OPTION_NO_CHANGE &&
		opt.not_indexed == OPTION_NO_CHANGE &&
		opt.offline == OPTION_NO_CHANGE &&
		opt.temporary == OPTION_NO_CHANGE) {
		usage();
		exit(1);
	}
*/

	int exitcode = 0;

    if (optind >= argc) {
		return do_files("", "*.*");
	}

    while (optind < argc) {
		string path = argv[optind++];
		if (path.length() == 0)
			continue;
		string filespec;
		if (is_directory(path)) {
			filespec = "*.*";
		} else {
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];

			_splitpath(path.c_str(), drive, dir, fname, ext);
			char temp[_MAX_PATH];
			_makepath(temp, drive, dir, "", "");
			if (strlen(temp) == 0)
				path = "";
			else
				path = temp;

			_makepath(temp, "", "", fname, ext);
			filespec = temp;
		}

		int rv = do_files(path, filespec);
		if (rv) {
			if (opt.abort)
				return rv;
			else
				exitcode = 1;
		}
    }

	return exitcode;
}
