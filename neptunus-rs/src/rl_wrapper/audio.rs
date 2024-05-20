use crate::drop_impl;

pub struct Sound(raylib_ffi::Sound);
pub struct Music(raylib_ffi::Music);

drop_impl! {Sound: UnloadSound, Music: UnloadMusicStream}

// TODO: implement Sound and Music

pub struct AudioDevice;

impl AudioDevice {
    pub fn init() -> Self {
        unsafe {
            raylib_ffi::InitAudioDevice();
            Self
        }
    }
}

impl Drop for AudioDevice {
    fn drop(&mut self) {
        unsafe {
            raylib_ffi::CloseAudioDevice();
        }
    }
}