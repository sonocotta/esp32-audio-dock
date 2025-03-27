#pragma once

#include <string.h>
#include <tas5805m.hpp>

#include "command.hpp"
#include "argtable3/argtable3.h"

extern tas5805m Tas5805m;

class GainCommand : public Command
{
    static inline const char *TAG = "CMD.GAIN";

private:

    static char* gain_ix_to_string(int gain_ix)
    {
        static char buf[16];
        int gain = -gain_ix * 5;
        snprintf(buf, sizeof(buf), "%d.%ddB", gain / 10, gain % 10);
        return buf;
    }

    static int int_to_gain_ix(int gain)
    {
        return -gain / 5;
    }

    // Handler function for the "gain" command
    static int gain_command_handler(int argc, char **argv)
    {
        int nerrors = arg_parse(argc, argv, (void **)&gain_args);
        if (nerrors > 0)
        {
            arg_print_errors(stderr, gain_args.end, "gain");
            ESP_LOGE("CMD", "Invalid command usage");
            return 1;
        }

        if (gain_args.gain->count == 0)
        {
            int gain;
            Tas5805m.getAnalogGain(&gain);
            ESP_LOGI(TAG, "Current gain is %s", gain_ix_to_string(gain));
            return 0;
        }

        int _gain = gain_args.gain->ival[0];
        int gain_ix = int_to_gain_ix(_gain);
        if (gain_ix < TAS5805M_MAX_GAIN || gain_ix > TAS5805M_MIN_GAIN)
        {
            ESP_LOGI(TAG, "Invalid gain level! Must be between -155 and 0");
            return 1;
        }

        ESP_LOGI(TAG, "Setting gain to %s", gain_ix_to_string(gain_ix)); 
        Tas5805m.setAnalogGain(gain_ix);
        return 0;
    }

public:
    struct GainArgs
    {
        struct arg_int *gain;
        struct arg_end *end;
    };

    static inline GainArgs gain_args = {
        arg_int0(NULL, NULL, "<gain>", "Gain level, -155..0, -155 = -15.5dB, 0 = 0dB"),
        arg_end(1)};

    String getName()
    {
        return "gain";
    };

    esp_console_cmd_t getCommand()
    {
        return {
            .command = "gain",
            .help = "Set the gain level",
            .hint = NULL,
            .func = &gain_command_handler,
            .argtable = &gain_args};
    }
};