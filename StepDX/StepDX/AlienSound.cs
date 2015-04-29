using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

using Microsoft.DirectX;
using Microsoft.DirectX.DirectSound;

namespace StepDX
{
    class AlienSound
    {
        private Device SoundDevice = null;

        private SecondaryBuffer jump = null;
        private SecondaryBuffer die = null;
        private SecondaryBuffer defeat = null;
        private SecondaryBuffer victory = null;
        private SecondaryBuffer attack = null;

        public AlienSound(Form form)
        {
            SoundDevice = new Device();
            SoundDevice.SetCooperativeLevel(form, CooperativeLevel.Priority);

            Load(ref jump, "../../wav/ready.wav");
            Load(ref die, "../../wav/death.wav");
            Load(ref defeat, "../../wav/defeat.wav");
            Load(ref victory, "../../wav/victory.wav");
            Load(ref attack, "../../wav/attack.wav");
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

        public void Defeat()
        {
            if (defeat == null)
                return;

            if (!defeat.Status.Playing)
                defeat.Play(0, BufferPlayFlags.Default);
        }

        public void Victory()
        {
            if (victory == null)
                return;

            if (!victory.Status.Playing)
                victory.Play(0, BufferPlayFlags.Default);
        }

        public void Attack()
        {
            if (attack == null)
                return;

            if (!attack.Status.Playing)
                attack.Play(0, BufferPlayFlags.Default);
        }
    }
}