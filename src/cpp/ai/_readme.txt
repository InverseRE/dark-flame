DarkFlame Copyright (C) 2014 Alexey Shumeiko

This file is part of DarkFlame.

DarkFlame is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DarkFlame is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DarkFlame.  If not, see <http://www.gnu.org/licenses/>.

For more details see LICENSE file.



   This is about AI idea.



    SCHEME

   +----------------------------+     +----------------------------+     +---+
   |                            |     |                            |     |   |
   |   Detectors                | ==> |   Analyzers                | <-- |   |
   | (a certain list of sensors |     | (data transfer functions)  | <-- |   |
   | used to gather info)       |     |                            |     |   |
   +----------------------------+     +----------------------------+     |   |
              ^ ^ ^                                | | |                 |   |
              | | |                                v v v                 | M |
   +----------------------------+     +----------------------------+     | o |
   |                            |     |                            |     | t |
   |   Adapters                 |     |   Inner World              | <-> | i |
   |                            |     | (representation of outer   |     | v |
   |   +----------------------+ |     | one, a bunch of different  | <-> | a |
   |   |   Outer World        | |     | parameters which is actual |     | t |
   |   +----------------------+ |     | and expected state of AI)  | <-> | o |
   +----------------------------+     +----------------------------+     | r |
              ^ ^ ^                                | | |                 | s |
              | | |                                v v v                 |   |
   +----------------------------+     +----------------------------+     |   |
   |                            |     |                            |     |   |
   |   Effectors                |     |   Controllers              | <-- |   |
   | (a set of executive tools) | <== | (simple rule tracking or   | <-- |   |
   |                            |     | directing AI)              |     |   |
   +----------------------------+     +----------------------------+     +---+



    TERMS

    Outer World - 'dwelling' of AI owner there it operates.

    Adapters - gateway API, a conversion from outer world's signals to
    a native API.

    Detectors - a set of the unique type parameters which will be taken by AI
    (outer world's actual state).

    Analyzer - functions which transfer outer parameters to inner parameters.

    Inner World, Representation - a set of parameters how they are known by AI,
    active signals sended by analyzers.

    Motivators - momentary active targets to achieve, every single motivator
    scans the inner parameters and/or other motivators and affects their value
    or state, can construct a new analyzers, controllers, motivators.

    Controllers - simple functions of tracing of internal state and formation
    of control signals for executive devices.

    Effectors - tools/devices to affect the outer world state, limited
    opportunities are assumed.



    LOGICAL RELATIONSHIPS

    Simple Reflex Arc (conditions > event > response).

    Complex Reflex Arc (conditions & events > event > responses).

    Continuous Tracking (tracking value > evaluation > regulation signals).

    Expanding (inner state > evaluation > new motivator).

    Collapsing (achieved target > verification > motivator abolition).

    Excitatory (gain of the motivators).

    Inhibition (attenuation of the motivators).

    Adaptation (motivator > analyzer's transfer function).

    Correction (motivator > affected inner parameters).

    Decision (motivator > controllers potentials).
