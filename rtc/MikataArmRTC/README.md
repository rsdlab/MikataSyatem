# MikataArm

## Overview

ROBOTICS MIKATA Arm RTC

## Description

Mikata Arm (ROBOTICS) Control RTC. This uses libmikataarm (https://github.com/ogata-lab/libmikataarm) as submodule.

### Input and Output



### Algorithm etc



### Basic Information

|  |  |
----|---- 
| Module Name | MikataArm |
| Description | ROBOTICS MIKATA Arm RTC |
| Version | 1.0.0 |
| Vendor | Ogata Labratory |
| Category | Manipulator |
| Comp. Type | STATIC |
| Act. Type | PERIODIC |
| Kind | DataFlowComponent |
| MAX Inst. | 1 |

### Activity definition

<table>
  <tr>
    <td rowspan="4">on_initialize</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_finalize</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_startup</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_shutdown</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td rowspan="4">on_activated</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td rowspan="4">on_deactivated</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td rowspan="4">on_execute</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_aborting</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_error</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td rowspan="4">on_reset</td>
    <td colspan="2">implemented</td>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
  <tr>
    <td>on_state_update</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>on_rate_changed</td>
    <td colspan="2"></td>
  </tr>
</table>

### InPorts definition


### OutPorts definition

#### JointStates



<table>
  <tr>
    <td>DataType</td>
    <td>RTC::TimedFloatSeq</td>
    <td></td>
  </tr>
  <tr>
    <td>IDL file</td>
    <td colspan="2">BasicDataType.idl</td>
  </tr>
  <tr>
    <td>Number of Data</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Semantics</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Occirrence frecency Period</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Operational frecency Period</td>
    <td colspan="2"></td>
  </tr>
</table>


### Service Port definition

#### manipMiddle



<table>
  <tr>
    <td>I/F Description</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td colspan="3">Interface</td>
  </tr>
  <tr>
    <td rowspan="9">JARA_ARM_ManipulatorCommonInterface_Middle</td>
    <td>Type</td>
    <td>JARA_ARM::ManipulatorCommonInterface_Middle</td>
    <tr>
      <td>Direction</td>
      <td>Provider</td>
    </tr>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>IDL file</td>
      <td>ManipulatorCommonInterface_MiddleLevel.idl</td>
    </tr>
    <tr>
      <td>Argument</td>
      <td></td>
    </tr>
    <tr>
      <td>Return Value</td>
      <td></td>
    </tr>
    <tr>
      <td>Exception</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
</table>

#### manipCommon



<table>
  <tr>
    <td>I/F Description</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td colspan="3">Interface</td>
  </tr>
  <tr>
    <td rowspan="9">JARA_ARM_ManipulatorCommonInterface_Common</td>
    <td>Type</td>
    <td>JARA_ARM::ManipulatorCommonInterface_Common</td>
    <tr>
      <td>Direction</td>
      <td>Provider</td>
    </tr>
    <tr>
      <td>Description</td>
      <td></td>
    </tr>
    <tr>
      <td>IDL file</td>
      <td>ManipulatorCommonInterface_Common.idl</td>
    </tr>
    <tr>
      <td>Argument</td>
      <td></td>
    </tr>
    <tr>
      <td>Return Value</td>
      <td></td>
    </tr>
    <tr>
      <td>Exception</td>
      <td></td>
    </tr>
    <tr>
      <td>PreCondition</td>
      <td></td>
    </tr>
    <tr>
      <td>PostCondition</td>
      <td></td>
    </tr>
  </tr>
</table>


### Configuration definition

#### port_name




<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">string</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>COM1</td>
    <td></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>

#### baudrate




<table>
  <tr>
    <td>DataType</td>
    <td colspan="2">int</td>
  </tr>
  <tr>
    <td>DefaultValue</td>
    <td>1000000</td>
    <td></td>
  </tr>
  <tr>
    <td>Unit</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Widget</td>
    <td colspan="2">text</td>
  </tr>
  <tr>
    <td>Step</td>
    <td colspan="2"></td>
  </tr>
  <tr>
    <td>Constraint</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Range</td>
    <td colspan="2"></td>
  </tr>
</table>


## Demo

## Requirement

## Setup

### Windows

### Ubuntu

## Usage

## Running the tests

## LICENCE

GPLv3


## References

https://github.com/sugarsweetrobotics/libdynamixel


## Author

Yuki Suga (ysuga@ysuga.net)
