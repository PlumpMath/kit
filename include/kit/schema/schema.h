#ifndef KIT_CONFIG_H
#define KIT_CONFIG_H

#include <memory>
#include "../meta/meta.h"
#include "../log/log.h"

template<class Mutex=kit::dummy_mutex>
class Schema
{
    public:
        using mutex_type = Mutex;
        
        Schema() = default;

        template<class TMutex>
        Schema(const std::shared_ptr<Meta<TMutex>>& m);
        
        // validate throws on error, check just returns false
        template<class TMutex>
        void validate(const std::shared_ptr<const Meta<TMutex>>& m) const;
        template<class TMutex>
        bool check(const std::shared_ptr<const Meta<TMutex>>& m) const {
            try{
                Log::Silencer ls;
                validate(m);
                return true;
            }catch(Error&){}
            return false;
        }

        // adds all schema fields with default values
        template<class TMutex>
        void add_missing_fields(std::shared_ptr<Meta<TMutex>>& m) const;

        // ignores fields marked as optional
        template<class TMutex>
        void add_required_fields(std::shared_ptr<Meta<TMutex>>& m) const;
        
        template<class TMutex>
        std::shared_ptr<Meta<TMutex>> make_default() const;

    private:
        std::shared_ptr<Meta<Mutex>> m_pMeta;
};

#include "schema.inl"

#endif
