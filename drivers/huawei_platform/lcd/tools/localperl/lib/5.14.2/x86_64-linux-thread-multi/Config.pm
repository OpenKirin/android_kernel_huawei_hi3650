# This file was created by configpm when Perl was built. Any changes
# made to this file will be lost the next time perl is built.

# for a description of the variables, please have a look at the
# Glossary file, as written in the Porting folder, or use the url:
# http://perl5.git.perl.org/perl.git/blob/HEAD:/Porting/Glossary

package Config;
use strict;
use warnings;
use vars '%Config';

# Skip @Config::EXPORT because it only contains %Config, which we special
# case below as it's not a function. @Config::EXPORT won't change in the
# lifetime of Perl 5.
my %Export_Cache = (myconfig => 1, config_sh => 1, config_vars => 1,
		    config_re => 1, compile_date => 1, local_patches => 1,
		    bincompat_options => 1, non_bincompat_options => 1,
		    header_files => 1);

@Config::EXPORT = qw(%Config);
@Config::EXPORT_OK = keys %Export_Cache;

# Need to stub all the functions to make code such as print Config::config_sh
# keep working

sub bincompat_options;
sub compile_date;
sub config_re;
sub config_sh;
sub config_vars;
sub header_files;
sub local_patches;
sub myconfig;
sub non_bincompat_options;

# Define our own import method to avoid pulling in the full Exporter:
sub import {
    shift;
    @_ = @Config::EXPORT unless @_;

    my @funcs = grep $_ ne '%Config', @_;
    my $export_Config = @funcs < @_ ? 1 : 0;

    no strict 'refs';
    my $callpkg = caller(0);
    foreach my $func (@funcs) {
	die qq{"$func" is not exported by the Config module\n}
	    unless $Export_Cache{$func};
	*{$callpkg.'::'.$func} = \&{$func};
    }

    *{"$callpkg\::Config"} = \%Config if $export_Config;
    return;
}

die "Perl lib version (5.14.2) doesn't match executable '$0' version ($])"
    unless $^V;

$^V eq 5.14.2
    or die "Perl lib version (5.14.2) doesn't match executable '$0' version (" .
	sprintf("v%vd",$^V) . ")";


sub FETCH {
    my($self, $key) = @_;

    # check for cached value (which may be undef so we use exists not defined)
    return exists $self->{$key} ? $self->{$key} : $self->fetch_string($key);
}

sub TIEHASH {
    bless $_[1], $_[0];
}

sub DESTROY { }

sub AUTOLOAD {
    require 'Config_heavy.pl';
    goto \&launcher unless $Config::AUTOLOAD =~ /launcher$/;
    die "&Config::AUTOLOAD failed on $Config::AUTOLOAD";
}

# tie returns the object, so the value returned to require will be true.
tie %Config, 'Config', {
    archlibexp => '/home/jenkins/zhoujian/localperl/lib/5.14.2/x86_64-linux-thread-multi',
    archname => 'x86_64-linux-thread-multi',
    cc => 'cc',
    d_readlink => 'define',
    d_symlink => 'define',
    dlext => 'so',
    dlsrc => 'dl_dlopen.xs',
    dont_use_nlink => undef,
    exe_ext => '',
    inc_version_list => ' ',
    intsize => '4',
    ldlibpthname => 'LD_LIBRARY_PATH',
    libpth => '/usr/local/lib /lib/x86_64-linux-gnu /lib/../lib /usr/lib/x86_64-linux-gnu /usr/lib/../lib /lib /usr/lib',
    osname => 'linux',
    osvers => '3.16.0-30-generic',
    path_sep => ':',
    privlibexp => '/home/jenkins/zhoujian/localperl/lib/5.14.2',
    scriptdir => '~/zhoujian/localperl/bin',
    sitearchexp => '/home/jenkins/zhoujian/localperl/lib/site_perl/5.14.2/x86_64-linux-thread-multi',
    sitelibexp => '/home/jenkins/zhoujian/localperl/lib/site_perl/5.14.2',
    so => 'so',
    useithreads => 'define',
    usevendorprefix => undef,
    version => '5.14.2',
};
