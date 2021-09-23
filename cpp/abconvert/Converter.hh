#ifndef EICAFTERBURNER_CONVERTER_HH
#define EICAFTERBURNER_CONVERTER_HH

#include <memory>

#include <HepMC3/Reader.h>
#include <HepMC3/Writer.h>
#include <afterburner/Afterburner.hh>
#include <functional>
#include <utility>


namespace ab{
    namespace abconv{
        class Converter {
        public:

            Converter(std::shared_ptr<HepMC3::Reader> reader,
                      std::shared_ptr<HepMC3::Writer> writer,
                      std::shared_ptr<ab::Afterburner> afterburner);
            void convert();

            void set_verbosity(int verbose) {
                _verbose = verbose;
            }

            void set_last_event_number(uint64_t last_event_number) {
                this->_last_event_number = last_event_number;
            }

            void set_first_event_number(uint64_t first_event_number) {
                this->_first_event_number = first_event_number;
            }

            void set_events_limit(uint64_t events_limit) {
                this->_events_limit = events_limit;
            }

            void set_after_process_callback(std::function<void(HepMC3::GenEvent&)> after_callback) {
                this->_ap_callback = std::move(after_callback);
            }

        private:
            std::shared_ptr<HepMC3::Reader> _reader;
            std::shared_ptr<HepMC3::Writer> _writer;
            std::shared_ptr<ab::Afterburner> _afterburner;
            int _verbose=0;
            uint64_t _first_event_number=0;
            uint64_t _last_event_number=0;
            uint64_t _events_limit=0;
            std::function<void(HepMC3::GenEvent&)> _ap_callback=nullptr;
            static void print_processed_events(long count);

            void get_beams_setup(const HepMC3::GenEvent& event);
        };
    }
}


#endif //EICAFTERBURNER_CONVERTER_HH
