#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "includes.h"

/* Files to test:
Device.h            Light.h          OffState.h   SetTemperatureCommand.h
DeviceState.h       LockCommand.h    OnCommand.h  SmartHomeSystem.h
doctest.h           LockedState.h    OnState.h    SmartThermostat.h
Doorlock.h          MacroRoutine.h   OpenState.h  SmartThermostatIntegrator.h
HomeCommand.h       MotionSensor.h   Room.h       TemperatureSensor.h
includes.h          NotifyCommand.h  Section.h    ToggleOnCommand.h
LegacyThermostat.h  OffCommand.h     Sensor.h     UnlockCommand.h
*/
using namespace std;

TEST_CASE("Device States")
{
    SUBCASE("OnState")
    {
        OnState on = OnState();
        CHECK(on.getDescription() == "On");
        CHECK(on.getType() == "Power");
    }
    SUBCASE("OffState")
    {
        OffState off = OffState();
        CHECK(off.getDescription() == "Off");
        CHECK(off.getType() == "Power");
    }
    SUBCASE("LockedState")
    {
        LockedState locked = LockedState();
        CHECK(locked.getDescription() == "Locked");
        CHECK(locked.getType() == "Lock");
    }
    SUBCASE("OpenState")
    {
        OpenState open = OpenState();
        CHECK(open.getDescription() == "Unlocked");
        CHECK(open.getType() == "Lock");
    }
}

TEST_CASE("Devices")
{
    SUBCASE("Device")
    {
        Light d = Light();
        CHECK(d.getId().substr(0, 5) == "Light");
        // Make sure that a error is thrown when notifying the device
        CHECK_THROWS(d.notify());
    }
    SUBCASE("Light")
    {
        Light l = Light();
        CHECK(l.getDeviceType() == "Light");
        CHECK(l.getStatus() == "Off");
        l.setState(OnState());
        CHECK(l.getStatus() == "On");
        l.setState(OffState());
        CHECK(l.getStatus() == "Off");
        CHECK_EQ(l.printState(), "Light " + l.getId() + ":\t" + l.getStatus());
    }
    SUBCASE("Doorlock")
    {
        Doorlock d = Doorlock();
        CHECK(d.getDeviceType() == "Doorlock");
        CHECK(d.getStatus() == "Locked");
        d.setState(LockedState());
        CHECK(d.getStatus() == "Locked");
        d.setState(OpenState());
        CHECK(d.getStatus() == "Unlocked");
        CHECK_EQ(d.printState(), "Doorlock " + d.getId() + ":\t" + d.getStatus());
    }
    SUBCASE("LegacyThermostat")
    {
        LegacyThermostat lt = LegacyThermostat(25);
        CHECK(lt.getTemperature() == 25.0);
        lt.increaseTemperature();
        CHECK(fabs(lt.getTemperature() - 25.1) < 0.0001);
        lt.decreaseTemperature();
        CHECK(fabs(lt.getTemperature() - 25.0) < 0.0001);
    }
    SUBCASE("SmartThermostat")
    {
        SmartThermostat st = SmartThermostat(25);
        st.setState(OnState());
        CHECK(st.getTemperature() == 25);
        st.setTemperature(30);
        CHECK(st.getTemperature() == 30);
        CHECK_EQ(st.printState(), "SmartThermostat " + st.getId() + ":\tOn\n\tTemperature: 30.000000");

        // test that "SmartThermostat is off. Cannot set temperature." is printed when getting and setting temperature on an off thermostat
        st.setState(OffState());
        CHECK(st.getTemperature() == -1);
        st.setTemperature(30);
        CHECK(st.getTemperature() == -1);
    }
    SUBCASE("SmartThermostatIntegrator")
    {
        LegacyThermostat lt = LegacyThermostat(25);
        SmartThermostatIntegrator sti = SmartThermostatIntegrator(&lt);
        sti.initialize();
        CHECK(sti.getDeviceType() == "SmartThermostat");
        CHECK(sti.getStatus() == "Off");
        sti.setState(OnState());
        CHECK(sti.getStatus() == "On");
        sti.setTemperature(13);
        CHECK(fabs(sti.getTemperature() - 13) < 0.0001);

        sti.setTemperature(15);
        CHECK(fabs(sti.getTemperature() - 15) < 0.0001);

        sti.setState(OffState());
        CHECK(sti.getTemperature() == -1);

        sti.setState(OnState());

        CHECK_EQ(sti.printState(), "SmartThermostatIntegrator " + sti.getId() + ":\t" + sti.getStatus() + "\n\tTemperature: " + std::to_string(sti.getTemperature()));
    }
}

TEST_CASE("Sensors")
{
    SUBCASE("MotionSensor")
    {
        MotionSensor m = MotionSensor();
        CHECK(m.getDeviceType() == "MotionSensor");
        CHECK(m.getStatus() == "Off");
        m.setState(OnState());
        CHECK(m.getStatus() == "On");
        m.setState(OffState());
        CHECK(m.getStatus() == "Off");
    }
    SUBCASE("TemperatureSensor")
    {
        TemperatureSensor t = TemperatureSensor();
        CHECK(t.getDeviceType() == "TemperatureSensor");
        CHECK(t.getStatus() == "Off");
        t.setState(OnState());
        CHECK(t.getStatus() == "On");
        t.setTemperature(25);
        CHECK(t.getTemperature() == 25);
    }
}

TEST_CASE("Commands")
{
    SUBCASE("OnCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            on.execute();
            CHECK(l.getStatus() == "On");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            OnCommand on = OnCommand(&d);
            on.execute();
            CHECK(d.getStatus() == "Locked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            OnCommand on = OnCommand(&st);
            on.execute();
            CHECK(st.getTemperature() == 25);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            OnCommand on = OnCommand(&t);
            on.execute();
            CHECK(t.getStatus() == "On");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            OnCommand on = OnCommand(&m);
            on.execute();
            CHECK(m.getStatus() == "On");
        }
    }
    SUBCASE("OffCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            OffCommand off = OffCommand(&l);
            off.execute();
            CHECK(l.getStatus() == "Off");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            OffCommand off = OffCommand(&d);
            off.execute();
            CHECK(d.getStatus() == "Locked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            OffCommand off = OffCommand(&st);
            off.execute();
            CHECK(st.getTemperature() == -1);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            OffCommand off = OffCommand(&t);
            off.execute();
            CHECK(t.getStatus() == "Off");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            OffCommand off = OffCommand(&m);
            off.execute();
            CHECK(m.getStatus() == "Off");
        }
    }
    SUBCASE("ToggleOnCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            ToggleOnCommand toggle = ToggleOnCommand(&l, false);
            toggle.execute();
            CHECK(l.getStatus() == "On");
            toggle.execute();
            CHECK(l.getStatus() == "Off");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            ToggleOnCommand toggle = ToggleOnCommand(&d, false);
            toggle.execute();
            CHECK(d.getStatus() == "Locked");
            toggle.execute();
            CHECK(d.getStatus() == "Locked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            ToggleOnCommand toggle = ToggleOnCommand(&st, false);
            toggle.execute();
            CHECK(st.getTemperature() == 25);
            toggle.execute();
            CHECK(st.getTemperature() == -1);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            ToggleOnCommand toggle = ToggleOnCommand(&t, false);
            toggle.execute();
            CHECK(t.getStatus() == "On");
            toggle.execute();
            CHECK(t.getStatus() == "Off");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            ToggleOnCommand toggle = ToggleOnCommand(&m, false);
            toggle.execute();
            CHECK(m.getStatus() == "On");
            toggle.execute();
            CHECK(m.getStatus() == "Off");
        }
    }
    SUBCASE("LockCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            LockCommand lock = LockCommand(&l);
            lock.execute();
            CHECK(l.getStatus() == "Off");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            LockCommand lock = LockCommand(&d);
            lock.execute();
            CHECK(d.getStatus() == "Locked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            st.setState(OnState());
            LockCommand lock = LockCommand(&st);
            lock.execute();
            CHECK(st.getTemperature() == 25);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            LockCommand lock = LockCommand(&t);
            lock.execute();
            CHECK(t.getStatus() == "Off");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            LockCommand lock = LockCommand(&m);
            lock.execute();
            CHECK(m.getStatus() == "Off");
        }
    }
    SUBCASE("UnlockCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            UnlockCommand unlock = UnlockCommand(&l);
            unlock.execute();
            CHECK(l.getStatus() == "Off");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            UnlockCommand unlock = UnlockCommand(&d);
            unlock.execute();
            CHECK(d.getStatus() == "Unlocked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            st.setState(OnState());
            UnlockCommand unlock = UnlockCommand(&st);
            unlock.execute();
            CHECK(st.getTemperature() == 25);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            UnlockCommand unlock = UnlockCommand(&t);
            unlock.execute();
            CHECK(t.getStatus() == "Off");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            UnlockCommand unlock = UnlockCommand(&m);
            unlock.execute();
            CHECK(m.getStatus() == "Off");
        }
    }
    SUBCASE("SetTemperatureCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            SetTemperatureCommand set = SetTemperatureCommand(&l, 25);
            set.execute();
            CHECK(l.getStatus() == "Off");
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            SetTemperatureCommand set = SetTemperatureCommand(&d, 25);
            set.execute();
            CHECK(d.getStatus() == "Locked");
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            st.setState(OnState());
            SetTemperatureCommand set = SetTemperatureCommand(&st, 30);
            set.execute();
            CHECK(st.getTemperature() == 30);
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            SetTemperatureCommand set = SetTemperatureCommand(&t, 25);
            set.execute();
            CHECK(t.getStatus() == "Off");
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            SetTemperatureCommand set = SetTemperatureCommand(&m, 25);
            set.execute();
            CHECK(m.getStatus() == "Off");
        }
    }
    SUBCASE("NotifyCommand")
    {
        SUBCASE("Light")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on);
            CHECK_THROWS(notify.execute());
            CHECK_NOTHROW(notify.filterExecute());
        }
        SUBCASE("Doorlock")
        {
            Doorlock d = Doorlock();
            UnlockCommand on = UnlockCommand(&d);
            NotifyCommand notify = NotifyCommand(&d, &on);
            CHECK_THROWS(notify.execute());
            CHECK_NOTHROW(notify.filterExecute());
        }
        SUBCASE("SmartThermostat")
        {
            SmartThermostat st = SmartThermostat(25);
            OnCommand on = OnCommand(&st);
            NotifyCommand notify = NotifyCommand(&st, &on);
            CHECK_THROWS(notify.execute());
            CHECK_NOTHROW(notify.filterExecute());
        }
        SUBCASE("TemperatureSensor")
        {
            TemperatureSensor t = TemperatureSensor();
            OnCommand on = OnCommand(&t);
            NotifyCommand notify = NotifyCommand(&t, &on);
            CHECK_THROWS(notify.execute());
            CHECK_NOTHROW(notify.filterExecute());
        }
        SUBCASE("MotionSensor")
        {
            MotionSensor m = MotionSensor();
            OnCommand on = OnCommand(&m);
            NotifyCommand notify = NotifyCommand(&m, &on);
            CHECK_THROWS(notify.execute());
            CHECK_NOTHROW(notify.filterExecute());
        }
        SUBCASE("Less Than")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "lt 50");
            CHECK_NOTHROW(notify.filterExecute("49"));
        }
        SUBCASE("Greater Than")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "gt 50");
            CHECK_NOTHROW(notify.filterExecute("51"));
        }
        SUBCASE("Equal")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "eq 50");
            CHECK_NOTHROW(notify.filterExecute("50"));
        }
        SUBCASE("Not Equal")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "ne 50");
            CHECK_NOTHROW(notify.filterExecute("51"));
        }
        SUBCASE("Greater Than or Equal")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "ge 50");
            CHECK_NOTHROW(notify.filterExecute("50"));
        }
        SUBCASE("Less Than or Equal")
        {
            Light l = Light();
            OnCommand on = OnCommand(&l);
            NotifyCommand notify = NotifyCommand(&l, &on, "le 50");
            CHECK_NOTHROW(notify.filterExecute("50"));
        }
    }
}

TEST_CASE("MacroRoutine")
{
    Light l1 = Light();
    MacroRoutine m = MacroRoutine(&l1, "Test");
    OnCommand on = OnCommand(&l1);
    OffCommand off = OffCommand(&l1);
    m.addCommand(&on);
    m.addCommand(&off);
    m.execute();
    m.removeCommand(&off);
    CHECK(m.getName().substr(0, 4) == "Test");
}

TEST_CASE("Rooms")
{
    Room r = Room("Living Room");
    Light l1 = Light();
    Light l2 = Light();
    r.addDevice(&l1);
    r.addDevice(&l2);
    r.removeDevice(&l1);
    CHECK(r.getId().substr(0, 4) == "Room");
    CHECK(r.printState() == "Room Living Room:\n" + l2.printState() + "\n");

    OnCommand on = OnCommand(&r);
    on.execute();
    CHECK(r.printState() == "Room Living Room:\n" + l2.printState() + "\n");
}

TEST_CASE("Sections")
{
    Section s = Section("Living Room");
    Room r = Room("Living Room");
    Light l1 = Light();
    Light l2 = Light();
    r.addDevice(&l1);
    r.addDevice(&l2);
    s.addRoom(&r);
    CHECK(s.getId().substr(0, 7) == "Section");
    CHECK(s.printState() == "Section Living Room:\n" + r.printState() + '\n');

    OnCommand on = OnCommand(&s);
    on.execute();
    CHECK('-' + s.printState() + '-' == "-Section Living Room:\n" + r.printState() + "\n-");

    s.removeRoom(&r);
}

TEST_CASE("Sensors")
{
    SUBCASE("MotionSensor")
    {
        Light l = Light();
        OnCommand on = OnCommand(&l);
        NotifyCommand notify = NotifyCommand(&l, &on);
        MotionSensor m = MotionSensor();
        CHECK(m.getDeviceType() == "MotionSensor");
        CHECK(m.getStatus() == "Off");
        m.setState(OffState());
        CHECK(m.getStatus() == "Off");
        m.setState(OnState());
        CHECK(m.getStatus() == "On");
        m.addDevice(&notify);
        m.trigger();
        m.printState();

        m.setState(OffState());
        CHECK(m.getStatus() == "Off");
        m.trigger();
    }
    SUBCASE("TemperatureSensor")
    {
        SmartThermostat st = SmartThermostat(25);
        SetTemperatureCommand set = SetTemperatureCommand(&st, 30);
        NotifyCommand notify = NotifyCommand(&st, &set, "gt 30");
        TemperatureSensor t = TemperatureSensor();
        CHECK(t.getDeviceType() == "TemperatureSensor");
        CHECK(t.getStatus() == "Off");
        t.setState(OnState());
        CHECK(t.getStatus() == "On");
        t.setTemperature(25);
        CHECK(t.getTemperature() == 25);
        t.addDevice(&notify);
        t.trigger();
        t.printState();

        t.setState(OffState());
        CHECK(t.getStatus() == "Off");
        t.trigger();

        t.removeDevice(&notify);
    }
}

TEST_CASE("SmartHomeSystem")
{
  SmartHomeSystem system = SmartHomeSystem();
  system.addSection("North");
  system.addSection("East");
  system.addSection("South");
  system.addSection("West");
  system.addRoom("Kitchen","North");
  system.addRoom("TVRoom" , "East");
  system.addRoom("Hallway","South");
  system.addRoom("Bedroom","West");
  system.addDevice(1,"Kitchen");
  system.addDevice(2,"Kitchen");
  system.addDevice(3,"Kitchen");
  system.addDevice(4,"Kitchen");
  system.addDevice(5,"Kitchen");
  system.addDevice(6,"Kitchen");
  system.addDevice(7,"Kitchen");
  system.removeDevice("Light");
  system.addSection("East");
  system.removeSection("Wayward");
  system.addRoom("Bedroom","West");
  system.addRoom("Bedroom","Wayward");
  system.removeRoom("Hall","");
  system.removeDevice("Light78");
  #if TRUE
  system.run();
  #endif
}