Summary: ADUCID library
Name: libaducid
Version: 3.0.0
Release: 1%{dist}
License: Apache License 2.0
Group: Applications/Libraries
Source: c-aducid.tgz
BuildRoot: /var/tmp/%{name}-root
%{?el5:Requires: libcurl}
%{?el6:Requires: curl}
%{?el7:Requires: curl}
BuildRequires: make
BuildRequires: gcc
%{?el5:BuildRequires: curl-devel}
%{?el6:BuildRequires: libcurl-devel}
%{?el7:BuildRequires: libcurl-devel}
Packager: Tomas Halman
%define pkgconfigdir %{_libdir}/pkgconfig
%define docdir %{_datarootdir}/doc/%{name}-%{version}

%description
ADUCID client library provides simplified usage of ADUCID infrastructure


%package devel
Summary: ADUCID development library
Group: Additional Development
%{?el5:BuildRequires: curl-devel}
%{?el6:BuildRequires: libcurl-devel}
%{?el7:BuildRequires: libcurl-devel}

%description devel
ADUCID client developement files

%prep
%setup -n c-aducid

%build
# VER1 = 3.0
# VER2 = 0
VER1=`echo %{version} | cut -d . -f 1,2`
VER2=`echo %{version} | cut -d . -f 3`
VER3=%{version}

#sed -r --in-place \
#    -e "s/^MINORVERSION=.+$/MINORVERSION=$VER2/" \
#    -e "s/MAJORVERSION=.+$/MAJORVERSION=$VER1/" \
#    c/Makefile
./configure --prefix=%{_prefix} --libdir=%{_libdir}
make


%install
VER1=`echo %{version} | cut -d . -f 1,2`
VER2=`echo %{version} | cut -d . -f 3`
VER3=%{version}

/bin/rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

# header files
install -d ${RPM_BUILD_ROOT}/%{_includedir}
install -m 644 src/aducid.h ${RPM_BUILD_ROOT}/%{_includedir}
install -m 644 src/aducid++.h ${RPM_BUILD_ROOT}/%{_includedir}

# pkg-config
install -d ${RPM_BUILD_ROOT}/%{pkgconfigdir}
sed -r < tools/libaducid.pc \
    -e "s#^libdir=.+\$#libdir=%{_libdir}#" \
    -e "s#^includedir=.+\$#includedir=%{_includedir}#" \
    > $RPM_BUILD_ROOT/%{pkgconfigdir}/libaducid.pc

sed -r < tools/libaducid.pc \
    -e "s#^libdir=.+\$#libdir=%{_libdir}#" \
    -e "s#^includedir=.+\$#includedir=%{_includedir}#" \
    -e "s#-laducid#-laducidpp#" \
    > $RPM_BUILD_ROOT/%{pkgconfigdir}/libaducidpp.pc

# examples
install -d $RPM_BUILD_ROOT/%{docdir}
for dir in doc/demos/* ; do
    make -C $dir clean
done
cp -r doc/demos $RPM_BUILD_ROOT/%{docdir}/

%clean
/bin/rm -rf $RPM_BUILD_ROOT

%files
%exclude %{_libdir}/*.la
%exclude %{_libdir}/*.lai
%{_libdir}/libaducid.so.%{version}
%{_libdir}/libaducidpp.so.%{version}

%files devel
%{pkgconfigdir}/libaducid.pc
%{pkgconfigdir}/libaducidpp.pc
%{_includedir}/aducid.h
%{_includedir}/aducid++.h
%{_libdir}/libaducid.so
%{_libdir}/libaducid.so.3
%{_libdir}/libaducidpp.so
%{_libdir}/libaducidpp.so.3
%doc %{docdir}
