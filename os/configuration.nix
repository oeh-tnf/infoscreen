{ config, pkgs, lib, infoscreen-pkg, ... }:

{
  imports = [
    ./usb_otg.nix
  ];

  boot = {
    # This was necessary for testing at /dev/lol, because of 2.4/5Ghz hybrid wifi
    extraModprobeConfig = ''
      options brcmfmac roamoff=1 feature_disable=0x82000
    '';
  };

  hardware.deviceTree.overlays = [
    {
      name = "putThatDamnRevisionInThere";
      dtsText = ''
        /dts-v1/;
        /plugin/;

        / {
          compatible = "brcm,bcm2837";

          fragment@0 {
            target-path = "/";
            __overlay__ {
              system {
                linux,revision = <0x902120>;
              };
            };
          };
        };
      '';
    }
  ];

  # We need that for wifi
  hardware.enableRedistributableFirmware = true;

  hardware.deviceTree.filter = "bcm2837-rpi-*.dtb";

  age.secrets.wifi.file = secrets/wifi.age;

  networking = {
    hostName = "tnf-infoscreen";
    useDHCP = false;
    interfaces = {
      wlan0 = {
        useDHCP = true;
      };
      usb0 = {
        useDHCP = false;
      };
    };
    wireless = {
      enable = true;
      secretsFile = config.age.secrets.wifi.path;
      networks = {
        "KEPLERnet" = {
          pskRaw = "ext:PSK_KEPLERNET";
        };
        # for testing
        "/dev/lol" = {
          pskRaw = "ext:PSK_DEVLOL";
        };
      };
    };
  };

  environment.systemPackages = with pkgs; [
    vim
    dtc
  ];

  fonts.packages = with pkgs; [
    redhat-official-fonts
  ];

  users = {
    mutableUsers = false;
    users.root = {
      openssh.authorizedKeys.keys = builtins.concatMap (admin: admin.sshKeys) (builtins.attrValues (import ../admins));
    };
  };

  services.openssh = {
    enable = true;
    settings = {
      PasswordAuthentication = false;
    };
  };

  services.logind = {
    extraConfig = ''
      NAutoVTs=0
      ReserveVT=N
    '';
  };

  systemd.services.tnf-infoscreen = {
    enable = true;
    after = [ "network.target" ];
    wantedBy = [ "default.target" ];
    serviceConfig = {
        Type = "simple";
        Restart = "always";
        ExecStart = "${infoscreen-pkg}/bin/tnf-infoscreen -platform linuxfb";
    };
  };

  # DO NOT CHANGE, unless you know exactly what you are doing
  system.stateVersion = "24.05";
}
