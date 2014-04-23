using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

using Microsoft.DirectX;
using Microsoft.DirectX.DirectSound;

namespace StepDX
{
    class GameSounds
    {
        private Device SoundDevice = null;

        private SecondaryBuffer jump = null;
        private SecondaryBuffer die = null;

        public GameSounds(Form form)
        {
            SoundDevice = new Device();
            SoundDevice.SetCooperativeLevel(form, CooperativeLevel.Priority);

            Load(ref jump, "../../jump.wav");
            Load(ref die, "../../die.wav");
        }

        private void Load(ref SecondaryBuffer buffer, string filename)
        {
            try
            {
                buffer = new SecondaryBuffer(filename, SoundDevice);
            }
            catch (Exception)
            {
                MessageBox.Show("Unable to load " + filename,
                                "Danger, Will Robinson", MessageBoxButtons.OK);
                buffer = null;
            }
        }

        public void Jump()
        {
            if (jump == null)
                return;

            if (!jump.Status.Playing)
                jump.Play(0, BufferPlayFlags.Default);
        }

        public void Die()
        {
            if (die == null)
                return;

            if (!die.Status.Playing)
                die.Play(0, BufferPlayFlags.Default);
        }
    }
}