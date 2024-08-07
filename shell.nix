let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.05";
  pkgs = import nixpkgs { config = {}; overlays = []; };
in

pkgs.mkShell {
  packages = with pkgs; [
    stdenv.cc.cc.lib        # libc
    cmake                   # build system
    glfw-wayland-minecraft  # OpenGL windowing library
    freetype                # font rendering
    harfbuzzFull            # text shaping
    alsa-lib                # audio
    doxygen                 # documentation
  ];

  LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib:";
}
