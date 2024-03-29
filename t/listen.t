#!/usr/bin/env perl

use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/../perl/lib";

use Data::Dumper;
use JSON;
use Test::More;
use Dynatron::Client;

use constant DYNATRON => "$FindBin::Bin/../dynatron";

my $PORT = int( 2000 + rand(60000) );
my $INIT = {
  verb   => 'listen',
  config => { port => $PORT },
};

my $pid = fork;
die "Can't fork: $!" unless defined $pid;
unless ($pid) {
  exec DYNATRON() => encode_json $INIT;
}

diag "dynatron $pid";
sleep 1;

ok my $cl = Dynatron::Client->new( port => $PORT ), 'client created';

eval { $cl->send( { verb => "ping" } ) };
ok !$@, "send OK";
my $got = eval { $cl->receive };
ok !$@, "receive OK";
like $got->{version}, qr{^\d+\.\d\d$}, "got version";
diag "dynatron version ", $got->{version};

eval {
  $cl->send(
    { verb   => 'tell',
      target => ['core'],
      msg    => {
        verb   => 'clone',
        name   => 'core_1',
        config => {},
      },
    }
  );
};
sleep 2;

done_testing();

kill 2, $pid;
diag "killed $pid";
wait;

# vim:ts=2:sw=2:et:ft=perl

