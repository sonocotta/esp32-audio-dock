#pragma once

#include <string.h>
#include "generators/generator.hpp"
#include <commands/command.hpp>
#include "argtable3/argtable3.h"

extern SineGenerator sineGenerator;

class SineToneCommand : public Command
{
    static constexpr const char *TAG = "CMD.TONE.SINE";

private:

    static int tone_cmd_handler(int argc, char **argv)
    {
        int nerrors = arg_parse(argc, argv, (void **)&tone_args);
        if (nerrors > 0)
        {
            arg_print_errors(stderr, tone_args.end, "tone");
            ESP_LOGE("CMD", "Invalid command usage");
            return 1;
        }

        const char *action = tone_args.action->sval[0]; // Get action argument

        if (strcmp(action, "play") == 0)
        {
            // Ensure frequency is provided for "play"
            if (tone_args.freq->count == 0)
            {
                ESP_LOGE("CMD", "Error: 'play' requires a frequency argument.");
                return 1;
            }

            int frequency = tone_args.freq->ival[0];
            int volume = (tone_args.volume->count > 0) ? tone_args.volume->ival[0] : 10;

            ESP_LOGI("CMD", "Playing tone at %d Hz with amplitude %d bit", frequency, volume);
        
            sineGenerator.setFrequency(frequency);
            sineGenerator.setAmplitude(volume);
            sineGenerator.start();
        }
        else if (strcmp(action, "stop") == 0)
        {
            // "stop" should NOT require frequency or volume
            if (tone_args.freq->count > 0 || tone_args.volume->count > 0)
            {
                ESP_LOGE("CMD", "Error: 'stop' does not take frequency or volume parameters.");
                return 1;
            }

            ESP_LOGI("CMD", "Stopping tone");
            sineGenerator.stop();
        }
        else
        {
            ESP_LOGE("CMD", "Unknown action: %s", action);
            return 1;
        }

        return 0;
    }

public:
    struct ToneArgs
    {
        struct arg_str *action;
        struct arg_int *freq;
        struct arg_int *volume;
        struct arg_end *end;
    };

    static inline ToneArgs tone_args = {
        arg_str1(NULL, NULL, "<play|stop>", "Action: play or stop"),
        arg_int0(NULL, NULL, "[freq]", "Frequency in Hz (1..8000 Hz, default is 440 Hz)"),
        arg_int0(NULL, NULL, "[volume]", "Volume level (0-16 bit, default: 10)"),
        arg_end(3)
    };

    esp_console_cmd_t getCommand()
    {
        return {
            .command = "sin",
            .help = "Control sine tone playback. Usage: tone play [freq] [volume] | tone stop",
            .hint = NULL,
            .func = &tone_cmd_handler,
            .argtable = &tone_args
        };
    }

};