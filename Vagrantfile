# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "precise64"
  config.vm.box_url = "http://files.vagrantup.com/precise64.box"

  $provision_set_mirror = <<SCRIPT
echo "deb mirror://mirrors.ubuntu.com/mirrors.txt precise main restricted universe multiverse" > /etc/apt/sources.list
echo "deb mirror://mirrors.ubuntu.com/mirrors.txt precise-updates main restricted universe multiverse" >> /etc/apt/sources.list
echo "deb mirror://mirrors.ubuntu.com/mirrors.txt precise-backports main restricted universe multiverse" >> /etc/apt/sources.list
echo "deb mirror://mirrors.ubuntu.com/mirrors.txt precise-security main restricted universe multiverse" >> /etc/apt/sources.list
apt-get update
apt-get install -y build-essential nasm git automake
SCRIPT

  $provision_watchman = <<SCRIPT
# https://github.com/facebook/watchman
cd /tmp
git clone https://github.com/facebook/watchman.git
cd watchman
./autogen.sh
./configure
make && make install 
SCRIPT

  $provision_build = <<SCRIPT
cd /vagrant
make watch > compile.log 2> compile-err.log & 
SCRIPT

  config.vm.provision :shell, inline: $provision_set_mirror
  #config.vm.provision :shell, inline: $provision_watchman
  #config.vm.provision :shell, inline: $provision_build
end
