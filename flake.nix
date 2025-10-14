{
  inputs = {
    nixpkgs.url = github:NixOS/nixpkgs/nixos-25.05;
    systems.url = github:nix-systems/default;
    nixos-hardware.url = github:NixOS/nixos-hardware/master;

    agenix.url = github:ryantm/agenix;
    agenix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, systems, agenix, nixos-hardware }: {
    packages =
      let
        eachSystem = nixpkgs.lib.genAttrs (import systems);
      in
      eachSystem (system: {
        tnfInfoscreen = nixpkgs.legacyPackages.${system}.qt6.callPackage ./app {};
        default = self.packages.${system}.tnfInfoscreen;
      });
    apps =
      let
        eachSystem = nixpkgs.lib.genAttrs (import systems);
      in
      eachSystem (system: {
        agenix = {
          type = "app";
          program = "${agenix.packages.${system}.agenix}/bin/agenix";
        };
      });
    nixosConfigurations.tnf-infoscreen = nixpkgs.lib.nixosSystem {
      system = "aarch64-linux";
      specialArgs = {
        infoscreen-pkg = self.packages.aarch64-linux.tnfInfoscreen;
      };
      modules = [
        "${nixpkgs}/nixos/modules/installer/sd-card/sd-image-aarch64.nix"
        "${nixos-hardware}/raspberry-pi/4/pkgs-overlays.nix"
        agenix.nixosModules.default
        os/configuration.nix
      ];
    };

  };
}

