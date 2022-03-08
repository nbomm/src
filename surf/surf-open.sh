#!/bin/sh
#
# See the LICENSE file for copyright and license details.
#

xidfile="/tmp/tabbed-surf.xid"
uri=""
src_path="$(realpath $0 | xargs -I % dirname %)"

if [ "$#" -gt 0 ];
then
	uri="$1"
else
	uri="$(awk -F '"' '/^\#define HOMEPAGE/ {print $2}' $src_path/config.h)"
fi

runtabbed() {
	tabbed -dn tabbed-surf -r 2 surf -e '' "$uri" >"$xidfile" \
		2>/dev/null &
}

if [ ! -r "$xidfile" ];
then
	runtabbed
else
	xid=$(cat "$xidfile")
	xprop -id "$xid" >/dev/null 2>&1
	if [ $? -gt 0 ];
	then
		runtabbed
	else
		surf -e "$xid" "$uri" >/dev/null 2>&1 &
	fi
fi
