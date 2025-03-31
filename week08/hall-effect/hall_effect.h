#ifndef HALL_EFFECT_H_INCLUDED
#define HALL_EFFECT_H_INCLUDED

#include <functional>

template <typename T>
class StateMachine
{
public:
  StateMachine() : handler{&StateMachine::do_nothing}
  {
  }

  StateMachine(StateMachine const& other) = delete;
  StateMachine& operator=(StateMachine const& other) = delete;
  StateMachine(StateMachine&& other)
  {
    other->handler = this->handler;
    this->clear_handler();
  }
  
  StateMachine& operator=(StateMachine&& other)
  {
    other->handler = this->handler;
    this->clear_handler();
    return *this;
  }

  virtual ~StateMachine() {}

  void handle_continue()
  {
    // Youch. Can't use dynamic_cast here because RTTI is disabled.
    this->handler((T*) this);
  }
protected:
  void set_handler(std::function<void(T* _this)> handler)
  {
    this->handler = handler;
  }
  
  void clear_handler() {
    this->set_handler(&StateMachine::do_nothing);
  }
private:
  void do_nothing()
  {
  }
  
  std::function<void(T* _this)> handler;
};

/**
 * Interface to the SN74HC14N hall effect sensor.
 *
 * The class is implemented using the Arduino Wire1 object. If the lifetimes of
 * any two instances of this class overlap, the behavior is undefined.
 */
class HallEffect : public StateMachine<HallEffect>
{
public:
  HallEffect();
  ~HallEffect();

  bool is_failed() const;
  void start_reading();
  bool has_fresh_value() const;
  int  get_value() const;
private:
  bool verify_slave_device();
  void request_register(int reg);
  int get_byte_blocking();
  void set_oneburst();
  void fetch_high_byte();
  void fetch_low_byte();
  void read_high_byte();
  void read_low_byte();
  void recalc_value();

  int          address{-1};
  int          high_reg_byte{0};
  unsigned int low_reg_byte{0};
  unsigned int last_value{0};
  bool         transfer_in_progress{false};
  mutable bool value_fresh{false};
  bool         failed{false};
};

#endif // HALL_EFFECT_H_INCLUDED
