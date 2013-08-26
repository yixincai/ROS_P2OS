"""autogenerated by genpy from p2os_driver/GripperState.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import p2os_driver.msg

class GripperState(genpy.Message):
  _md5sum = "300b38b2a4173deb725df02fa70fc70b"
  _type = "p2os_driver/GripperState"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """GripState grip
LiftState lift

================================================================================
MSG: p2os_driver/GripState
# direction -1 is inward, +1 is outward, 0 is stationary
uint32 state
int32 dir
bool inner_beam
bool outer_beam
bool left_contact
bool right_contact

================================================================================
MSG: p2os_driver/LiftState
# direction -1 is downard, +1 is upward, 0 is stationary
int32 state
int32 dir
float32 position

"""
  __slots__ = ['grip','lift']
  _slot_types = ['p2os_driver/GripState','p2os_driver/LiftState']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       grip,lift

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GripperState, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.grip is None:
        self.grip = p2os_driver.msg.GripState()
      if self.lift is None:
        self.lift = p2os_driver.msg.LiftState()
    else:
      self.grip = p2os_driver.msg.GripState()
      self.lift = p2os_driver.msg.LiftState()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_Ii4B2if.pack(_x.grip.state, _x.grip.dir, _x.grip.inner_beam, _x.grip.outer_beam, _x.grip.left_contact, _x.grip.right_contact, _x.lift.state, _x.lift.dir, _x.lift.position))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.grip is None:
        self.grip = p2os_driver.msg.GripState()
      if self.lift is None:
        self.lift = p2os_driver.msg.LiftState()
      end = 0
      _x = self
      start = end
      end += 24
      (_x.grip.state, _x.grip.dir, _x.grip.inner_beam, _x.grip.outer_beam, _x.grip.left_contact, _x.grip.right_contact, _x.lift.state, _x.lift.dir, _x.lift.position,) = _struct_Ii4B2if.unpack(str[start:end])
      self.grip.inner_beam = bool(self.grip.inner_beam)
      self.grip.outer_beam = bool(self.grip.outer_beam)
      self.grip.left_contact = bool(self.grip.left_contact)
      self.grip.right_contact = bool(self.grip.right_contact)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_Ii4B2if.pack(_x.grip.state, _x.grip.dir, _x.grip.inner_beam, _x.grip.outer_beam, _x.grip.left_contact, _x.grip.right_contact, _x.lift.state, _x.lift.dir, _x.lift.position))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.grip is None:
        self.grip = p2os_driver.msg.GripState()
      if self.lift is None:
        self.lift = p2os_driver.msg.LiftState()
      end = 0
      _x = self
      start = end
      end += 24
      (_x.grip.state, _x.grip.dir, _x.grip.inner_beam, _x.grip.outer_beam, _x.grip.left_contact, _x.grip.right_contact, _x.lift.state, _x.lift.dir, _x.lift.position,) = _struct_Ii4B2if.unpack(str[start:end])
      self.grip.inner_beam = bool(self.grip.inner_beam)
      self.grip.outer_beam = bool(self.grip.outer_beam)
      self.grip.left_contact = bool(self.grip.left_contact)
      self.grip.right_contact = bool(self.grip.right_contact)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_Ii4B2if = struct.Struct("<Ii4B2if")
